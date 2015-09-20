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
#include "board/console.h"
#include "hal/stm32f4/stm32f4_gpio.h"
#include "hal/stm32f4/stm32f4_gpio_functions.h"
#include "hal/stm32f4/stm32f4_pwm.h"
#include "hal/stm32f4/stm32f4_rcc.h"

void board_showSystemClocks()
{
    STM32F4_ClockFrequencies_t clocks;

    stm32f4_rccGetClocksFrequencies(&clocks);
    console_write("board: Available clocks:\n");
    console_write("board: sysclk: %d kHz\n", clocks.sysclk_frequency_hz / 1000);
    console_write("board: hclk  : %d kHz\n", clocks.hclk_frequency_hz / 1000);
    console_write("board: pclk1 : %d kHz\n", clocks.pclk1_frequency_hz / 1000);
    console_write("board: pclk2 : %d kHz\n", clocks.pclk2_frequency_hz / 1000);
}

bool board_strobeInit(GPIOHandle_t *gpio_handle, GPIOConfig_t config)
{
    // Configure GPIO.
    STM32F4_GPIOConfig_t gpio_config;
    gpio_config.general_config = config;
    gpio_config.function = GPIO_DIGITAL_PIN;
    gpio_config.speed = GPIO_SPEED_50MHz;
    gpio_config.mode = GPIO_MODE_OUT;
    gpio_config.output_type = GPIO_OUTPUT_PUSHPULL;

    if(!stm32f4_gpioInit(gpio_handle, gpio_config))
    {
        console_write("board: Failed to initialize GPIO for %s\n", gpio_handle->name);
        return false;
    }

    return true;
}

bool board_engineInit(PWMHandle_t *pwm_handle, PWMConfig_t pwm_config, GPIOConfig_t gpio_general_config)
{
    // Configure GPIO.
    STM32F4_GPIOConfig_t gpio_config;
    gpio_config.general_config = gpio_general_config;
    gpio_config.function = stm32f4_timerToPinFunction(&pwm_handle->timer);
    gpio_config.speed = GPIO_SPEED_100MHz;
    gpio_config.mode = GPIO_MODE_ALTERNATE;
    gpio_config.output_type = GPIO_OUTPUT_PUSHPULL;

    if(!stm32f4_gpioInit(&pwm_handle->gpio, gpio_config))
    {
        console_write("board: Failed to initialize GPIO for %s\n", pwm_handle->gpio.name);
        return false;
    }

    // Configure PWM.
    if(!stm32f4_pwmInit(pwm_handle, pwm_config))
    {
        console_write("board: Failed to initialize PWM for %s\n", pwm_handle->gpio.name);
        return false;
    }

    return true;
}
