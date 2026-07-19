set(src_dirs
	I2C/i2c_driver.c
	SPI/spi_driver.c
	GPIO/gpio_driver.c
	WIFI/wifi.c)

set(include_dirs
	I2C
	SPI
	GPIO
	./
	WIFI)

set(requires
	Middlewares
    driver)

idf_component_register(SRCS "${src_dirs}"
					   INCLUDE_DIRS "${include_dirs}"
					   REQUIRES "${requires}"
					   REQUIRES driver esp_netif esp_event nvs_flash  lwip json spiffs esp_wifi)
component_compile_options(-ffast-math -O3 -Wno-error=format=-Wno-format)