//=============================================================================================
//
// Filename   : stm32f4_pwm.c
// Author     : Kuba Sejdak
// Created on : 14.09.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#include "stm32f4_pwm.h"
#include "board/console.h"
#include "CMSIS/stm32f4xx.h"

//=============================================================================================
// INTERFACE FUNCTIONS
//=============================================================================================

bool stm32f4_pwmInit(PWMHandle_t *handle, PWMConfig_t *config)
{
    // Configure timer.
    STM32F4_TimerConfig_t timer_config;
    timer_config.counter_mode = COUNTER_MODE_UP;
    timer_config.clock_division = CLOCK_DIVISION_1;
    timer_config.repetition_counter = 0;

    float period_ms = config->timer_config.use_period ? config->timer_config.period_ms : ((1.0f / config->timer_config.frequency_hz) * 1000);
    if(!stm32f4_timerSetPeriodConfig(&handle->timer, period_ms, &timer_config)) {
        console_write("pwm: Failed to set config for timer event frequency\n");
        return false;
    }
    handle->period = timer_config.period;

    if(!stm32f4_timerInit(&handle->timer, &timer_config)) {
        console_write("pwm: Failed to initialize PWM timer\n");
        return false;
    }

    // Configure PWM channel.
    STM32F4_OutputCompareConfig_t oc_config;
    oc_config.mode = OUTPUT_COMPARE_MODE_PWM2;
    oc_config.output_state = OUTPUT_COMPARE_STATE_ENABLE;
    oc_config.polarity = OUTPUT_COMPARE_POLARITY_LOW;
    oc_config.pulse = timer_config.period * (float) (config->pulse_width_perc / 100.0f);
    console_write("pwm: Signal width: %d%%, period: %d, pulse: %d\n", config->pulse_width_perc, timer_config.period, oc_config.pulse);

    if(!stm32f4_outputCompareInit(&handle->timer, &oc_config)) {
        console_write("pwm: Failed to initialize PWM output compare mode\n");
        return false;
    }

    stm32f4_outputComparePreloadConfig(&handle->timer, OUTPUT_COMPARE_PRELOAD_ENABLE);
    return true;
}

void pwm_activate(PWMHandle_t *handle)
{
    timer_activate(&handle->timer);
}

void pwm_deactivate(PWMHandle_t *handle)
{
    timer_deactivate(&handle->timer);
}

void pwm_setPulseWidthPerc(PWMHandle_t *handle, uint32_t width_perc)
{
    uint16_t pulse = handle->period * (float) (width_perc / 100.0f);
    stm32f4_setOutputComparePulse(&handle->timer, pulse);
}
