#include "spi_driver.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "SPI_Driver";

esp_err_t Spi_Init(Spi_Config_t *config)
{
    if(config == NULL)
    {
        ESP_LOGE(TAG, "Config is NULL");
        return ESP_ERR_INVALID_ARG;
    }

    spi_bus_config_t busCfg = {
        .mosi_io_num = config->mosiPin,
        .miso_io_num = config->misoPin,
        .sclk_io_num = config->sckPin,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 240 * 320 * 2 + 8
    };

    esp_err_t ret = spi_bus_initialize(SPI2_HOST, &busCfg, SPI_DMA_CH_AUTO);
    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "SPI bus init failed: %d", ret);
        return ret;
    }

    ESP_LOGI(TAG, "SPI bus initialized on SPI2, speed=%dMHz",
             config->clockSpeedHz / 1000000);
    return ESP_OK;
}


/**
 * @brief Register an SPI device on SPI2 bus
 * 
 * @param csPin CS pin number
 * @param queueSize Queue size for SPI transactions 单位bits
 * @return Spi_Handle_t SPI device handle
*/
Spi_Handle_t Spi_Register_Device(int csPin, int queueSize)
{
    spi_device_interface_config_t devCfg = {
        .clock_speed_hz = 10 * 1000 * 1000,
        .mode = 0,
        .spics_io_num = csPin,
        .queue_size = queueSize,
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0
    };

    spi_device_handle_t handle;

    esp_err_t ret = spi_bus_add_device(SPI2_HOST, &devCfg, &handle);
    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "SPI device register failed (CS pin %d): %d", csPin, ret);
        return NULL;
    }

    ESP_LOGI(TAG, "SPI device registered (CS pin %d)", csPin);
    return (Spi_Handle_t)handle;
}

void Spi_Transmit(Spi_Handle_t handle, const uint8_t *data, size_t length)
{
    if(handle == NULL || data == NULL || length == 0)
    {
        return;
    }

    spi_transaction_t trans = {
        .length = length * 8,
        .tx_buffer = data
    };

    spi_device_transmit((spi_device_handle_t)handle, &trans);
}

void Spi_Transmit_16Bit(Spi_Handle_t handle, uint16_t data)
{
    uint8_t dataBuf[2] = {(data >> 8) & 0xFF, data & 0xFF};
    Spi_Transmit(handle, dataBuf, 2);
}