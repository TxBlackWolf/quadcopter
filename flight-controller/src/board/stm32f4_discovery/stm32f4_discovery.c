//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_discovery.c
// Author     : Kuba Sejdak
// Created on : 22.07.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "stm32f4_discovery.h"
#include "board/board.h"
#include "hal/stm32f4/stm32f4_gpio.h"
#include "hal/stm32f4/stm32f4_gpio_functions.h"
#include "hal/stm32f4/stm32f4_pwm.h"

bool board_strobeInit(GPIOHandle_t gpio_handle, GPIOConfig_t config)
{
    STM32F4_GPIOConfig_t gpio_config;
    gpio_config.general_config = config;
    gpio_config.function = GPIO_DIGITAL_PIN;
    gpio_config.speed = GPIO_SPEED_50MHz;
    gpio_config.mode = GPIO_MODE_OUT;
    gpio_config.output_type = GPIO_OUTPUT_PUSHPULL;

    return stm32f4_gpioInit(gpio_handle, gpio_config);
}

bool board_engineInit(PWMHandle_t pwm_handle, PWMConfig_t config)
{
    return false;
}
