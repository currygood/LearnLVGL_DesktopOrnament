#include "gpio_driver.h"
#include "esp_log.h"

static const char *TAG = "GPIO_Driver";

esp_err_t Gpio_Init(gpio_num_t gpioNum, Gpio_Mode_t mode)
{
    gpio_config_t ioConf = {
        .pin_bit_mask = (1ULL << gpioNum),
        .intr_type = GPIO_INTR_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE
    };

    switch(mode)
    {
        case GPIO_OUTPUT:
            ioConf.mode = GPIO_MODE_OUTPUT;
            break;
        case GPIO_INPUT:
            ioConf.mode = GPIO_MODE_INPUT;
            break;
        case GPIO_INPUT_PULLUP:
            ioConf.mode = GPIO_MODE_INPUT;
            ioConf.pull_up_en = GPIO_PULLUP_ENABLE;
            break;
        case GPIO_OD_OUTPUT:
            ioConf.mode = GPIO_MODE_OUTPUT_OD;
            break;
        default:
            ESP_LOGE(TAG, "Invalid GPIO mode");
            return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret = gpio_config(&ioConf);
    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "GPIO %d init failed", gpioNum);
    }

    return ret;
}

void Gpio_Set_Level(gpio_num_t gpioNum, uint8_t level)
{
    gpio_set_level(gpioNum, level);
}

uint8_t Gpio_Get_Level(gpio_num_t gpioNum)
{
    return gpio_get_level(gpioNum);
}

void Gpio_Toggle(gpio_num_t gpioNum)
{
    uint8_t currentLevel = gpio_get_level(gpioNum);
    gpio_set_level(gpioNum, !currentLevel);
}

esp_err_t Gpio_Install_Isr_Service(int flags)
{
    esp_err_t ret = gpio_install_isr_service(flags);
    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "GPIO ISR service install failed: %s", esp_err_to_name(ret));
    }
    return ret;
}

esp_err_t Gpio_Set_Intr_Type(gpio_num_t gpioNum, gpio_int_type_t intrType)
{
    esp_err_t ret = gpio_set_intr_type(gpioNum, intrType);
    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "GPIO %d set intr type failed: %s", gpioNum, esp_err_to_name(ret));
    }
    return ret;
}

esp_err_t Gpio_Isr_Handler_Add(gpio_num_t gpioNum, gpio_isr_t isrHandler, void *args)
{
    esp_err_t ret = gpio_isr_handler_add(gpioNum, isrHandler, args);
    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "GPIO %d ISR handler add failed: %s", gpioNum, esp_err_to_name(ret));
    }
    return ret;
}

esp_err_t Gpio_Intr_Enable(gpio_num_t gpioNum)
{
    esp_err_t ret = gpio_intr_enable(gpioNum);
    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "GPIO %d intr enable failed: %s", gpioNum, esp_err_to_name(ret));
    }
    return ret;
}