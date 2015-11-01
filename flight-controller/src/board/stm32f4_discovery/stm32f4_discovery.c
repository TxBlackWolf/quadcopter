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
#include "hal/stm32f4/CMSIS/stm32f4xx.h"
#include "hal/stm32f4/stm32f4_gpio.h"
#include "hal/stm32f4/stm32f4_gpio_functions.h"
#include "hal/stm32f4/stm32f4_pwm.h"
#include "hal/stm32f4/stm32f4_rcc.h"
#include "hal/stm32f4/stm32f4_nvic.h"

void board_showSystemClocks()
{
    STM32F4_ClockFrequencies_t clocks;

    stm32f4_rccGetClocksFrequencies(&clocks);
    console_write("board: Available clocks:\n");
    console_write("board: sysclk          : %d kHz\n", clocks.sysclk_frequency_hz / 1000);
    console_write("board: hclk (AHB bus)  : %d kHz\n", clocks.hclk_frequency_hz / 1000);
    console_write("board: pclk1 (APB1 bus): %d kHz\n", clocks.pclk1_frequency_hz / 1000);
    console_write("board: pclk2 (APB2 bus): %d kHz\n", clocks.pclk2_frequency_hz / 1000);
}

bool board_strobeInit(GPIOHandle_t *gpio_handle, GPIOConfig_t gpio_general_config, TimerHandle_t *timer_handle, TimerConfig_t timer_general_config)
{
    // Configure GPIO.
    STM32F4_GPIOConfig_t gpio_config;
    gpio_config.general_config = gpio_general_config;
    gpio_config.function = GPIO_DIGITAL_PIN;
    gpio_config.speed = GPIO_SPEED_50MHz;
    gpio_config.mode = GPIO_MODE_OUT;
    gpio_config.output_type = GPIO_OUTPUT_PUSHPULL;

    if(!stm32f4_gpioInit(gpio_handle, gpio_config)) {
        console_write("board: Failed to initialize GPIO for %s\n", gpio_handle->name);
        return false;
    }

    // Configure timer.
    STM32F4_TimerConfig_t timer_config;
    timer_config.counter_mode = COUNTER_MODE_UP;
    timer_config.clock_division = CLOCK_DIVISION_1;
    timer_config.repetition_counter = 0;

    float period_ms = timer_general_config.use_period ? timer_general_config.period_ms : ((1.0f / timer_general_config.frequency_hz) * 1000);
    if(!stm32f4_timerSetPeriodConfig(timer_handle, period_ms, &timer_config)) {
        console_write("board: Failed to set config for timer event frequency\n");
        return false;
    }

    if(!stm32f4_timerInit(timer_handle, timer_config)) {
        console_write("board: Failed to initialize strobe timer\n");
        return false;
    }

    // Configure NVIC.
    IRQConfig_t nvic_config;
    nvic_config.channel = TIM3_IRQn;
    nvic_config.channel_preemption_priority = 0;
    nvic_config.channel_subpriority = 0;
    nvic_config.enabled = true;
    stm32f4_nvicInitIRQ(&nvic_config);

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

    if(!stm32f4_gpioInit(&pwm_handle->gpio, gpio_config)) {
        console_write("board: Failed to initialize GPIO for %s\n", pwm_handle->gpio.name);
        return false;
    }

    // Configure PWM.
    if(!stm32f4_pwmInit(pwm_handle, pwm_config)) {
        console_write("board: Failed to initialize PWM for %s\n", pwm_handle->gpio.name);
        return false;
    }

    return true;
}
