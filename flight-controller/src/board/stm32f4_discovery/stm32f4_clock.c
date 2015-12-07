//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_clock.c
// Author     : Kuba Sejdak
// Created on : 05.12.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "stm32f4_clock.h"
#include "stm32f4_discovery_pinout.h"
#include "board/clock.h"
#include "board/console.h"
#include "hal/timer.h"
#include "hal/stm32f4/stm32f4_nvic.h"
#include "hal/stm32f4/stm32f4_timer.h"

bool clock_initPeriodicTimer()
{
    TimerHandle_t timer_handle;
    timer_handle.device = PERIODIC_EVENT_TIMER;
    timer_handle.channel = PERIODIC_EVENT_TIMER_CHANNEL;

    // Configure timer.
    STM32F4_TimerConfig_t timer_config;
    timer_config.counter_mode = COUNTER_MODE_UP;
    timer_config.clock_division = CLOCK_DIVISION_1;
    timer_config.repetition_counter = 0;

    if(!stm32f4_timerSetPeriodConfig(&timer_handle, (float) CLOCK_PERIODIC_TIMER_PERIOD_MS, &timer_config)) {
        console_write("board: Failed to set config for timer event frequency\n");
        return false;
    }

    if(!stm32f4_timerInit(&timer_handle, timer_config)) {
        console_write("board: Failed to initialize periodic timer\n");
        return false;
    }

    // Configure NVIC.
    IRQConfig_t nvic_config;
    nvic_config.channel = stm32f4_timerToIRQChannel(&timer_handle, TIMER_IRQ_UPDATE);
    nvic_config.channel_preemption_priority = 0;
    nvic_config.channel_subpriority = 0;
    nvic_config.enabled = true;
    stm32f4_nvicInitIRQ(&nvic_config);

    return stm32f4_registerEventCallback(&timer_handle, TIMER_IRQ_UPDATE, clock_processPeriodicEvents);
}

