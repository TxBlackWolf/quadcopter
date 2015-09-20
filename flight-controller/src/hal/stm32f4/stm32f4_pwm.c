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
#include "board/console.h"
#include "CMSIS/stm32f4xx.h"

//---------------------------------------------------------------------------------------------------------------
// HELPER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------
// INTERFACE FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

bool stm32f4_pwmInit(PWMHandle_t *handle, PWMConfig_t config)
{
    // Configure timer.
    STM32F4_TimerConfig_t timer_config;
    timer_config.prescaler = 0;
    timer_config.counter_mode = COUNTER_MODE_UP;
    timer_config.period = stm32f4_timerFrequencyToPeriod(&handle->timer, config.frequency_hz);
    handle->period = timer_config.period;
    timer_config.clock_division = CLOCK_DIVISION_1;
    timer_config.repetition_counter = 0;

    if(!stm32f4_timerInit(&handle->timer, timer_config))
    {
        console_write("pwm: Failed to initialize PWM timer\n");
        return false;
    }

    // Configure PWM channel.
    STM32F4_OutputCompareConfig_t oc_config;
    oc_config.mode = OUTPUT_COMPARE_MODE_PWM2;
    oc_config.output_state = OUTPUT_COMPARE_STATE_ENABLE;
    oc_config.polarity = OUTPUT_COMPARE_POLARITY_LOW;
    oc_config.pulse = timer_config.period * (float) (config.pulse_width_perc / 100.0f);
    console_write("pwm: Signal width: %d%%, period: %d, pulse: %d\n", config.pulse_width_perc, timer_config.period, oc_config.pulse);

    if(!stm32f4_outputCompareInit(&handle->timer, handle->channel, oc_config))
    {
        console_write("pwm: Failed to initialize PWM output compare mode\n");
        return false;
    }

    stm32f4_outputComparePreloadConfig(&handle->timer, handle->channel, OUTPUT_COMPARE_PRELOAD_ENABLE);
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

void pwm_setFrequency(PWMHandle_t *handle, uint32_t frequency_hz)
{
}

void pwm_setPulseWidthPerc(PWMHandle_t *handle, uint32_t width_perc)
{
    uint16_t pulse = handle->period * (float) (width_perc / 100.0f);
    stm32f4_setOutputComparePulse(&handle->timer, handle->channel, pulse);
}
