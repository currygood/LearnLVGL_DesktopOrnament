#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "gpio_driver.h"

#define SPI_SCK_GPIO   4
#define SPI_MOSI_GPIO  5
#define SPI_MISO_GPIO  6

typedef struct {
    int clockSpeedHz;
    int sckPin;
    int mosiPin;
    int misoPin;
} Spi_Config_t;

typedef void* Spi_Handle_t;

esp_err_t Spi_Init(Spi_Config_t *config);

Spi_Handle_t Spi_Register_Device(int csPin, int queueSize);

void Spi_Transmit(Spi_Handle_t handle, const uint8_t *data, size_t length);

void Spi_Transmit_16Bit(Spi_Handle_t handle, uint16_t data);

#endif