set(include_dirs "." "./UI/generated" "./UI/custom" "./UI/generated/guider_customer_fonts" "./LCD_Touch" "./Weather" "./AID64")

file(GLOB_RECURSE SOURCES "*/*.c")

set(requires
    driver
    BSP
	lvgl)

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS "${include_dirs}"
					   REQUIRES ${requires} esp_adc esp_timer driver esp_lvgl_port esp_wifi nvs_flash esp_http_server esp_http_client lwip json spiffs protocomm)

component_compile_options(-ffast-math -O3 -Wno-format)
add_compile_options(-fdiagnostics-color=always)
add_compile_options(-Wno-missing-braces)