# ESP32-S3 + ESP-IDF 移植 LVGL 到 SSD1306 OLED (128×64 I2C)

## 一、项目结构

```
First_LVGL/
├── main/
│   └── main.c                          # 应用入口
├── components/
│   ├── BSP/
│   │   └── I2C/
│   │       ├── i2c_driver.h            # I2C 引脚/频率配置
│   │       └── i2c_driver.c            # I2C 总线初始化、设备添加、读写
│   ├── Middlewares/
│   │   └── OLED/
│   │       ├── OLED.h                  # 地址宏、函数声明
│   │       └── OLED.c                  # OLED 初始化、LVGL 集成、格式转换
│   └── lvgl/                           # LVGL 库
│       └── lv_conf.h                   # LVGL 配置（颜色深度等）
```

---

## 二、关键配置

### 2.1 I2C 引脚 (`i2c_driver.h`)

```c
#define I2C_PORT      I2C_NUM_0
#define I2C_SDA_GPIO  21          // 避开 UART0(1) 和 Strapping 引脚(2)
#define I2C_SCL_GPIO  20
#define I2C_FREQ      400000      // 400kHz
```

### 2.2 LVGL 颜色深度 (`lv_conf.h`)

```c
#define LV_COLOR_DEPTH  1         // 1-bit 单色，匹配 SSD1306
```

### 2.3 OLED 地址 (`OLED.h`)

```c
#define OLED_ADDR  0x3C           // SSD1306 默认 I2C 地址
```

---

## 三、核心代码

### 3.1 main.c — 应用入口

```c
void app_main(void)
{
    i2c_master_bus_handle_t i2c_bus = NULL;

    // 1. 初始化 I2C 总线
    esp_err_t ret = I2c_Init_Bus(I2C_PORT, I2C_SDA_GPIO, I2C_SCL_GPIO, I2C_FREQ, &i2c_bus);
    if (ret != ESP_OK) {
        ESP_LOGE("MAIN", "I2C bus init failed: %s", esp_err_to_name(ret));
        return;
    }

    // 2. 初始化 OLED 硬件
    ret = OLED_Init(i2c_bus);
    if (ret != ESP_OK) {
        ESP_LOGE("MAIN", "OLED init failed: %s", esp_err_to_name(ret));
        return;
    }

    // 3. 初始化 LVGL + 绑定 OLED
    OLED_LVGL_Init();

    // 4. 创建 UI
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello, LVGL!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    // 5. 主循环
    while (1) {
        OLED_LVGL_Task();
        vTaskDelay(pdMS_TO_TICKS(6));
    }
}
```

### 3.2 OLED.c — LVGL 集成（关键部分）

**双缓冲区设计：**

```c
// SSD1306 格式（垂直字节排列），直接发送到 OLED 硬件
uint8_t OLED_DisplayBuf[8 * 128];           // 1024 字节

// LVGL I1 格式（水平位排列），供 LVGL 渲染
static uint8_t lvgl_draw_buf[8 + 8 * 128];  // 1032 字节（含 8 字节调色板）
```

**LVGL 初始化：**

```c
void OLED_LVGL_Init(void)
{
    lv_init();

    lv_display_t *disp = lv_display_create(128, 64);
    lv_display_set_buffers(disp, (void *)lvgl_draw_buf, NULL,
                           sizeof(lvgl_draw_buf), LV_DISPLAY_RENDER_MODE_DIRECT);
    lv_display_set_flush_cb(disp, lvgl_flush_cb);

    // 每 1ms 提供心跳
    esp_timer_create_args_t timer_args = {
        .callback = &lvgl_tick_cb,
        .name = "lvgl_tick"
    };
    esp_timer_handle_t lvgl_tick_timer;
    esp_timer_create(&timer_args, &lvgl_tick_timer);
    esp_timer_start_periodic(lvgl_tick_timer, 1000);
}
```

**格式转换函数（核心难点）：**

```c
/*
 * LVGL I1 水平格式 → SSD1306 垂直格式
 *
 * LVGL I1:   像素(x,y) = buf[y*16 + x/8] 的 bit(7 - x%8)   ← MSB 优先
 * SSD1306:   像素(x,y) = buf[(y/8)*128 + x] 的 bit(y%8)      ← bit0=顶部
 */
static void lvgl_to_ssd1306(uint8_t *src, uint8_t *dst)
{
    int x, y;
    memset(dst, 0xFF, 1024);   // 预填暗色背景

    for (y = 0; y < 64; y++) {
        for (x = 0; x < 128; x++) {
            int src_byte = y * 16 + (x >> 3);
            int src_bit  = 7 - (x & 0x07);        // LVGL: MSB 优先

            if (src[src_byte] & (1 << src_bit)) {
                int dst_byte = (y >> 3) * 128 + x;
                int dst_bit  = y & 0x07;
                dst[dst_byte] &= ~(1 << dst_bit); // 亮色文字：清 bit
            }
        }
    }
}
```

**Flush 回调：**

```c
static void lvgl_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    lvgl_to_ssd1306(&lvgl_draw_buf[8], OLED_DisplayBuf);  // 跳过 8 字节调色板
    OLED_Update();
    lv_display_flush_ready(disp);
}
```

**LVGL 任务处理：**

```c
void OLED_LVGL_Task(void)
{
    lv_timer_handler();
}
```

---

## 四、踩坑记录

### 坑 1：I2C 总线未初始化

**现象**：OLED 完全不显示。

**原因**：`i2c_master_bus_handle_t` 初始化为 NULL，没有调用 `I2c_Init_Bus()` 就传入 `OLED_Init()`。

**解决**：在 `main.c` 中先调用 `I2c_Init_Bus()` 再调用 `OLED_Init()`。

---

### 坑 2：I2C 引脚冲突

**现象**：`ESP_ERR_INVALID_STATE` 错误。

**原因**：GPIO1 是 UART0 TX，GPIO2 是 Strapping 引脚，冲突。

**解决**：改用 GPIO21 (SDA) 和 GPIO20 (SCL)。

---

### 坑 3：看门狗超时（Task Watchdog）

**现象**：`task_wdt: Task watchdog got triggered`，backtrace 停在 `lv_refr.c` 的 `layer_reshape_draw_buf`。

**原因**：LVGL I1 格式需要额外 **8 字节调色板空间**。`_calculate_draw_buf_size` 计算：

```
stride(16) × height(64) + 调色板(2色 × 4字节) = 1024 + 8 = 1032 字节
```

但缓冲区只有 1024 字节，导致 `lv_draw_buf_reshape` 返回 NULL，渲染死循环。

**解决**：缓冲区改为 1032 字节（`8 + 8*128`）。

---

### 坑 4：显示乱码/不全

**现象**：屏幕大部分点亮，但内容混乱。

**原因**：LVGL I1 和 SSD1306 的字节排列完全不同，不能直接共用缓冲区。

| | LVGL I1（水平） | SSD1306（垂直） |
|---|---|---|
| 1 字节含义 | 同行 8 个水平像素 | 同列 8 个垂直像素 |
| 像素 (x,y) 位置 | `y*16 + x/8` 字节 | `(y/8)*128 + x` 字节 |

**解决**：双缓冲区设计 + 格式转换函数 `lvgl_to_ssd1306()`。

---

### 坑 5：MSB/LSB 位序错误

**现象**：显示内容虽然有，但字符变形、不全。

**原因**：LVGL I1 使用 **MSB 优先**（bit7 = 像素0），但转换函数用了 LSB 优先（bit0 = 像素0），导致每个字节内 8 个像素左右镜像翻转。

**解决**：`src_bit = 7 - (x & 0x07)` 而非 `x & 0x07`。

---

### 坑 6：颜色反转

**现象**：文字是暗的，背景是亮的（反相）。

**原因**：某些 OLED 模块的像素极性是反的（bit 0 = 亮，bit 1 = 暗）。

**解决**：预填 `0xFF`（暗色背景），文字处清 bit（亮色文字）。

---

## 五、数据流全景

```
LVGL 渲染
    │
    ▼
lvgl_draw_buf[1032]          ← LVGL I1 水平格式（含 8 字节调色板）
    │
    │  lvgl_to_ssd1306()     ← 跳过调色板，位转置 + 颜色反转
    ▼
OLED_DisplayBuf[1024]        ← SSD1306 垂直格式
    │
    │  OLED_Update()         ← I2C 逐页发送
    ▼
SSD1306 OLED 屏幕
```

---

## 六、调试技巧

1. **先不用 LVGL 测试 OLED**：直接用 `OLED_Clear()` + `OLED_Update()` 看屏幕是否清空，确认 I2C 通信正常
2. **遇到看门狗**：检查缓冲区大小是否 ≥ LVGL 计算值（`_calculate_draw_buf_size`）
3. **显示乱码**：先确认 LVGL 格式和 OLED 格式的字节排列方式，再写转换函数
4. **颜色不对**：先试 `memset(dst, 0x00)` 和 `memset(dst, 0xFF)` 两种预填，确认 OLED 模块的像素极性