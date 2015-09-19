//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_pwm.c
// Author     : Kuba Sejdak
// Created on : 14.09.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "stm32f4_pwm.h"
#include "stm32f4_gpio.h"
#include "stm32f4_gpio_functions.h"
#include "CMSIS/stm32f4xx.h"

//---------------------------------------------------------------------------------------------------------------
// HELPER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------
// INTERFACE FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

bool stm32f4_pwmInit(PWMConfig_t config, PWMHandle_t handle)
{
    // Configure timer.
    STM32F4_TimerConfig_t timer_config;
    timer_config.prescaler = 0;
    timer_config.counter_mode = COUNTER_MODE_UP;

    // TODO: calculate 84 MHz frequency, do not hardcode it.
    // Timer period = (Timer tick frequency / PWM frequency) - 1
    uint16_t period = 84000000 / config.frequency_hz - 1;
    timer_config.period = period;
    timer_config.clock_division = CLOCK_DIVISION_1;
    timer_config.repetition_counter = 0;

    if(!stm32f4_timerInit(handle.timer.device, timer_config))
        return false;

    // Configure PWM channel.
    STM32F4_OutputCompareConfig_t oc_config;
    oc_config.mode = OUTPUT_COMPARE_MODE_PWM2;
    oc_config.output_state = OUTPUT_COMPARE_STATE_ENABLE;
    oc_config.polarity = OUTPUT_COMPARE_POLARITY_LOW;
    oc_config.pulse = config.pulse_width_perc * period;

    if(!stm32f4_outputCompareInit(handle.timer.device, config.channel, oc_config))
        return false;

    stm32f4_outputComparePreloadConfig(handle.timer.device, config.channel, OUTPUT_COMPARE_PRELOAD_ENABLE);

    // Configure GPIO.
    STM32F4_GPIOConfig_t gpio_config;
    gpio_config.general_config.direction = GPIO_DIRECTION_OUT;
    gpio_config.general_config.resistor_type = GPIO_RESISTOR_NONE;
    gpio_config.function = GPIO_AF_TIM4;    // TODO: this should be taken from device.
    gpio_config.speed = GPIO_SPEED_100MHz;
    gpio_config.mode = GPIO_MODE_ALTERNATE;
    gpio_config.output_type = GPIO_OUTPUT_PUSHPULL;

    return stm32f4_gpioInit(handle.gpio, gpio_config);
}

void pwm_activate(TimerDevice_t device)
{
    timer_activate(device);
}

void pwm_deactivate(TimerDevice_t device)
{
    timer_deactivate(device);
}

void pwm_setFrequency(uint32_t frequency_hz, TimerDevice_t device)
{
    //Timer_t *timer = stm32f4_timerGetRegisters(device);

    // TODO: calculate 84 MHz frequency, do not hardcode it.
    //uint16_t period = 84000000 / frequency_hz - 1;
    //timer->ARR = period;
}

void pwm_setPulseWidthPerc(uint32_t width_perc, TimerDevice_t device)
{
    // PWM pulse length = ((timer period + 1) * width percentage) / 100 - 1
    //Timer_t *timer = stm32f4_timerGetRegisters(device);
}

void pwm_setPulseWidthUsec(uint32_t width_us, TimerDevice_t device)
{
    //Timer_t *timer = stm32f4_timerGetRegisters(device);
}
