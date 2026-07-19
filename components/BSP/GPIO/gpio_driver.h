#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include "driver/gpio.h"

typedef enum {
    GPIO_OUTPUT,
    GPIO_INPUT,
    GPIO_INPUT_PULLUP,
    GPIO_OD_OUTPUT
} Gpio_Mode_t;

esp_err_t Gpio_Init(gpio_num_t gpioNum, Gpio_Mode_t mode);

void Gpio_Set_Level(gpio_num_t gpioNum, uint8_t level);

uint8_t Gpio_Get_Level(gpio_num_t gpioNum);

void Gpio_Toggle(gpio_num_t gpioNum);

esp_err_t Gpio_Install_Isr_Service(int flags);

esp_err_t Gpio_Set_Intr_Type(gpio_num_t gpioNum, gpio_int_type_t intrType);

esp_err_t Gpio_Isr_Handler_Add(gpio_num_t gpioNum, gpio_isr_t isrHandler, void *args);

esp_err_t Gpio_Intr_Enable(gpio_num_t gpioNum);

#endif