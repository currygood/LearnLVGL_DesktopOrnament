idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS ""
                    REQUIRES BSP Middlewares driver lvgl esp_lvgl_port spiffs)


spiffs_create_partition_image(storage ../img FLASH_IN_PROJECT)