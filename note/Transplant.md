# LVGL 移植到 SSD1306 OLED（通用篇）

> 适用于任何平台（STM32、ESP32、Arduino 等），聚焦 LVGL 与 SSD1306 之间的核心适配逻辑。

---

## 一、LVGL 配置

### 1.1 颜色深度

```c
// lv_conf.h
#define LV_COLOR_DEPTH  1    // 1-bit 单色，匹配 SSD1306
```

### 1.2 渲染模式

```c
lv_display_set_buffers(disp, buf, NULL, buf_size, LV_DISPLAY_RENDER_MODE_DIRECT);
```

| 模式 | 说明 |
|------|------|
| `DIRECT` | LVGL 直接渲染到用户提供的缓冲区，适合完整帧缓冲 |
| `FULL` | LVGL 内部分配双缓冲，内存开销大 |
| `PARTIAL` | 分块渲染，适合小内存 MCU |

---

## 二、缓冲区大小计算

LVGL 的 `_calculate_draw_buf_size` 对 I1 格式的计算公式：

```
总大小 = stride × height + 调色板大小
       = 16 × 64 + 2 × 4
       = 1024 + 8
       = 1032 字节
```

其中：
- `stride` = 对齐后的每行字节数 = `(width × bpp + 7) / 8` 向上取整到对齐边界
- 128 宽 × 1bpp → `(128 + 7) / 8 = 16` 字节/行
- 调色板 = `2 色 × 4 字节(RGBA)` = 8 字节

**缓冲区必须 ≥ 1032 字节**，否则 `lv_draw_buf_reshape` 返回 NULL，渲染死循环。

---

## 三、格式差异：为什么不能共用缓冲区

LVGL I1 和 SSD1306 的字节排列方式完全不同：

```
LVGL I1（水平位排列）：               SSD1306（垂直字节排列）：
┌─────────────────────────┐          ┌─────────────────────────┐
│ 1 字节 = 同行 8 个水平像素  │          │ 1 字节 = 同列 8 个垂直像素  │
│ 像素(x,y) → y×16 + x/8   │          │ 像素(x,y) → (y/8)×128 + x│
│       bit(7 - x%8)       │          │       bit(y%8)           │
│ MSB 优先 (bit7=像素0)     │          │ LSB 优先 (bit0=顶部像素)  │
└─────────────────────────┘          └─────────────────────────┘
```

**必须双缓冲区 + 格式转换。**

---

## 四、双缓冲区设计

```c
// SSD1306 格式（垂直字节排列），直接发送到 OLED 硬件
uint8_t oled_buf[8 * 128];           // 1024 字节

// LVGL I1 格式（水平位排列），供 LVGL 渲染
// 前 8 字节为调色板，后 1024 字节为像素数据
uint8_t lvgl_buf[8 + 8 * 128];       // 1032 字节
```

```
LVGL 渲染          格式转换            I2C 发送
    │                 │                   │
    ▼                 ▼                   ▼
lvgl_buf[1032]  →  oled_buf[1024]  →  SSD1306 屏幕
```

---

## 五、格式转换函数

```c
/*
 * LVGL I1 水平格式 → SSD1306 垂直格式
 *
 * LVGL:   像素(x,y) = src[y*16 + x/8] 的 bit(7 - x%8)    MSB 优先
 * SSD1306: 像素(x,y) = dst[(y/8)*128 + x] 的 bit(y%8)     bit0=顶部
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

### 转换要点

| 要点 | 说明 |
|------|------|
| 源位序 | `7 - (x & 0x07)` — LVGL I1 是 **MSB 优先**（bit7=像素0） |
| 目标位序 | `y & 0x07` — SSD1306 是 LSB 优先（bit0=顶部像素） |
| 颜色极性 | 预填 `0xFF` 或 `0x00` 取决于 OLED 模块的像素极性 |

---

## 六、Flush 回调

```c
static void lvgl_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    // 跳过调色板（前 8 字节），传入像素数据起始地址
    lvgl_to_ssd1306(&lvgl_buf[8], oled_buf);

    // 调用平台相关的 OLED 刷新函数
    oled_update();

    lv_display_flush_ready(disp);
}
```

---

## 七、LVGL 心跳

LVGL 需要一个 1ms 精度的定时器来驱动内部时钟：

```c
// 定时器回调：每 1ms 调用一次
static void lvgl_tick_cb(void)
{
    lv_tick_inc(1);
}
```

主循环中周期性调用：

```c
while (1) {
    lv_timer_handler();          // 处理 LVGL 定时任务
    delay_ms(5);                 // 建议 5~10ms 间隔
}
```

---

## 八、踩坑汇总

### 坑 1：缓冲区太小

**现象**：渲染死循环，看门狗/死机。

**原因**：I1 格式需要额外 8 字节调色板空间，总大小 1032 字节而非 1024 字节。

**解决**：`lvgl_buf[8 + 8*128]`。

---

### 坑 2：直接共用缓冲区

**现象**：屏幕内容混乱，几乎全亮。

**原因**：LVGL 水平位排列 ≠ SSD1306 垂直字节排列，直接发给 OLED 无法正确显示。

**解决**：双缓冲区 + 格式转换函数。

---

### 坑 3：MSB/LSB 位序搞反

**现象**：文字能显示但变形、不全，每个字符左右镜像。

**原因**：LVGL I1 是 **MSB 优先**（bit7=像素0），转换时用了 LSB 优先。

**解决**：`src_bit = 7 - (x & 0x07)`。

---

### 坑 4：颜色反转

**现象**：文字暗、背景亮（反相）。

**原因**：不同 OLED 模块的像素极性可能相反（bit 0=亮 vs bit 1=亮）。

**解决**：先试 `memset(dst, 0x00)` 和 `memset(dst, 0xFF)` 两种预填，确认模块极性后再确定用 `|=` 还是 `&= ~`。

---

## 九、调试技巧

1. **先不接 LVGL**：用纯色填充 OLED 缓冲区，确认硬件通信正常
2. **显示乱码时**：先确认 LVGL 和 OLED 的字节排列方式，再写转换函数
3. **颜色不对时**：切换 `0x00`/`0xFF` 预填 + `|=`/`&= ~` 的组合
4. **性能不足时**：转换函数 O(8192) 次循环，在 >100MHz MCU 上约 1~2ms，可接受