#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "LCD_Touch.h"
#include "lvgl.h"
#include "esp_log.h"
#include "i2c_driver.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "esp_lvgl_port.h"
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "wifi.h"
#include "esp_sntp.h"
#include "nvs_flash.h"
#include "Weather.h"
#include "esp_spiffs.h"

#define LV_CONF_INCLUDE_SIMPLE 1

#define LVGL_TICK_PERIOD_MS 5
#define LVGL_BUF_SIZE (LCD_HEIGHT * 10)

static const char *TAG = "Main";

static lv_color_t *Buf1 = NULL;
static lv_color_t *Buf2 = NULL;
static lv_indev_t *indev = NULL;

static void init_img_page_buffer(void)
{
	esp_vfs_spiffs_conf_t config = {
		.base_path = "/img",
		.partition_label = "storage",
		.max_files = 5,
		.format_if_mount_failed = false,
	};
	ESP_ERROR_CHECK(esp_vfs_spiffs_register(&config));
}

static void Lv_Flush_Callback(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    LCD_Set_Window(area->x1, area->y1, area->x2, area->y2);

    int32_t pixelCount = (int32_t)(area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1);

    if(pixelCount > 0)
    {
        LCD_Write_PixelData((uint16_t *)px_map, (uint32_t)pixelCount);
    }

    lv_display_flush_ready(disp);
}

static void Lv_Display_Init(void)
{
    Buf1 = (lv_color_t *)heap_caps_malloc(LVGL_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
    Buf2 = (lv_color_t *)heap_caps_malloc(LVGL_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);

    if(Buf1 == NULL || Buf2 == NULL)
    {
        ESP_LOGE("Main", "Failed to allocate LVGL buffers in PSRAM!");
        return;
    }

    ESP_LOGI("Main", "LVGL buffers allocated in PSRAM (%d KB each)", (LVGL_BUF_SIZE * sizeof(lv_color_t)) / 1024);

    lv_display_t *disp = lv_display_create(LCD_HEIGHT, LCD_WIDTH);

	if(disp == NULL)
    {
        ESP_LOGE("Main", "Failed to create LVGL display!");
        return;
    }
    lv_display_set_buffers(disp, Buf1, Buf2, LVGL_BUF_SIZE * sizeof(lv_color_t), LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_display_set_flush_cb(disp, Lv_Flush_Callback);
}

void indev_read_cb(lv_indev_t *indev, lv_indev_data_t *data)
{
    Touch_Point_t touchPoint;
    if(LCD_TOUCH_FT6336G_Get_Touch_Points(&touchPoint))
    {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = touchPoint.touchY;
        data->point.y = LCD_WIDTH - touchPoint.touchX;
		// ESP_LOGI(TAG, "Touch point: (%d, %d)", (int)data->point.x, (int)data->point.y);
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
		data->point.x = 0;
		data->point.y = 0;
    }
}

void mlvgl_init(void)
{
	lv_init();

	lvgl_port_cfg_t cfg = {
        .task_priority = 2,          // 任务优先级
        .task_stack = 32768,          // 任务栈大小
        .task_affinity = -1,         // CPU 亲和性
        .timer_period_ms = 5,        // 刷新周期（ms）
    };
    lvgl_port_init(&cfg);

    Lv_Display_Init();

	// 触摸屏输入设备初始化
	lvgl_port_lock(0);
	indev = lv_indev_create();

	lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);

	lv_indev_set_read_cb(indev, indev_read_cb);
	
	setup_ui(&guider_ui);
	events_init(&guider_ui);
	custom_init(&guider_ui);

	lvgl_port_unlock();

	vTaskDelete(NULL);
}

static void Lvgl_Task(void *pvParameter)
{
    (void)pvParameter;

    mlvgl_init();

    vTaskDelete(NULL);
}

static void sntp_finished_cb(struct timeval *tv)
{
	struct tm t;
	localtime_r(&tv->tv_sec,&t);
    set_home_time(&guider_ui,t.tm_year + 1900,t.tm_mon + 1,t.tm_mday,t.tm_hour +8 ,t.tm_min,t.tm_sec,t.tm_wday);
}


void WIFI_Connect_Task(void *pvParameter)
{
    (void)pvParameter;

    vTaskDelay(pdMS_TO_TICKS(3000));

    Wifi_Init();

    while(!Wifi_Is_Connected())
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    ESP_LOGI("WifiConnect", "WiFi connected");


	if(!esp_sntp_enabled())
	{
		esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
		esp_sntp_setservername(0, "cn.pool.ntp.org");
		esp_sntp_setservername(1, "ntp.aliyun.com");
		esp_sntp_setservername(2, "pool.ntp.org");
		esp_sntp_set_time_sync_notification_cb(sntp_finished_cb);
		esp_sntp_init();

	}

	static bool wifi_can_connected=true;

	while(1)
	{
		if(Wifi_Is_Connected() && wifi_can_connected)
		{
			set_wifi_visible(&guider_ui,true);
			wifi_can_connected = false;
		}
		
		if(!Wifi_Is_Connected() && !wifi_can_connected)
		{
			set_wifi_visible(&guider_ui,false);
			wifi_can_connected = true;
		}
		vTaskDelay(pdMS_TO_TICKS(5000));
	}
}

void app_main(void)
{
    i2c_master_bus_handle_t i2cBusHandle = NULL;
    esp_err_t ret;

	ESP_LOGI(TAG, "Initializing image page buffer...");
    init_img_page_buffer();

    ESP_LOGI(TAG, "Initializing NVS flash...");
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_LOGI(TAG, "NVS flash initialized successfully");

    ESP_LOGI(TAG, "Initializing I2C bus...");
    ret = I2c_Init_Bus(I2C_PORT, (gpio_num_t)I2C_SDA_GPIO, (gpio_num_t)I2C_SCL_GPIO, I2C_FREQ, &i2cBusHandle);
    if(ret != ESP_OK || i2cBusHandle == NULL)
    {
        ESP_LOGE(TAG, "Failed to initialize I2C bus!");
        while(1) { vTaskDelay(pdMS_TO_TICKS(1000)); }
    }
    ESP_LOGI(TAG, "I2C bus initialized successfully (SDA:%d SCL:%d Freq:%dHz)", I2C_SDA_GPIO, I2C_SCL_GPIO, I2C_FREQ);

    ESP_LOGI(TAG, "Initializing LCD + Touch screen...");
    LCD_TOUCH_Init(i2cBusHandle);

    ESP_LOGI(TAG, "Free heap before LVGL: %d bytes", (int)esp_get_free_heap_size());
    ESP_LOGI(TAG, "Free SPIRAM before LVGL: %d bytes", (int)heap_caps_get_free_size(MALLOC_CAP_SPIRAM));

	ESP_LOGI(TAG, "Starting LVGL task...");
    BaseType_t taskRet = xTaskCreatePinnedToCore(
        Lvgl_Task,
        "Lvgl_Task",
        8192,
        NULL,
        5,
        NULL,
        1
    );

    if(taskRet != pdPASS)
    {
        ESP_LOGE("Main", "Failed to create Lvgl_Task!");
        while(1) { vTaskDelay(pdMS_TO_TICKS(1000)); }
    }

    vTaskDelay(pdMS_TO_TICKS(100));

    ESP_LOGI(TAG, "Free heap after LVGL init: %d bytes", (int)esp_get_free_heap_size());

    ESP_LOGI(TAG, "Starting WiFi task...");
    xTaskCreatePinnedToCore(
        WIFI_Connect_Task,
        "WIFI_Connect_Task",
        4096,
        NULL,
        1,
        NULL,
        0
    );

    ESP_LOGI(TAG, "Starting Weather task...");
    weather_start();

    ESP_LOGI(TAG, "All tasks started! Free heap: %d bytes", (int)esp_get_free_heap_size());

    while(1)
	{
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}