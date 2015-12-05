//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_timer_irq.c
// Author     : Kuba Sejdak
// Created on : 25.10.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "hal/timer.h"
#include "stm32f4_timer.h"
#include "CMSIS/stm32f4xx.h"

#include <stdlib.h>
#include <stdint.h>

#define STM32F4_TIMER_MAX_CALLBACK_COUNT    5

static TimerEventCallback_t tim1_brk_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim1_up_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim1_com_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim1_trig_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim1_cc1_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim1_cc2_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim1_cc3_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim1_cc4_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim2_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim3_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim4_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim5_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim6_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim7_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim8_brk_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim8_up_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim8_com_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim8_trig_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim8_cc1_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim8_cc2_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim8_cc3_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim8_cc4_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim9_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim10_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim11_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim12_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim13_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
static TimerEventCallback_t tim14_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];

//---------------------------------------------------------------------------------------------------------------
// HELPER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

bool stm32f4_timerAddCallback(TimerEventCallback_t *callback_set, TimerEventCallback_t callback)
{
    for(int i = 0; i < STM32F4_TIMER_MAX_CALLBACK_COUNT; ++i) {
        if(callback_set[i] != NULL)
            continue;

        callback_set[i] = callback;
        return true;
    }

    return false;
}

bool stm32f4_timerRemoveCallback(TimerEventCallback_t *callback_set, TimerEventCallback_t callback, int *slots_used)
{
    for(int i = 0; i < STM32F4_TIMER_MAX_CALLBACK_COUNT; ++i) {
        if(callback_set[i] == NULL) {
            (*slots_used)--;
            continue;
        }

        if(callback_set[i] != callback)
            continue;

        callback_set[i] = NULL;
        (*slots_used)--;
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------------------------------------------
// TIMER INTERRUPT HANDLERS
//---------------------------------------------------------------------------------------------------------------

void TIM1_BRK_TIM9_IRQHandler()
{
    TimerHandle_t handle;
    if(TIM1->SR & TIMER_IRQ_BREAK){
        for(int i = 0; i < STM32F4_TIMER_MAX_CALLBACK_COUNT; ++i) {
            if(tim1_brk_callbacks[i])
                tim1_brk_callbacks[i]();
        }

        handle.device = STM32F4_TIMER_1;
        stm32f4_timerClearIRQPending(&handle, TIMER_IRQ_BREAK);
    }
    else {
        for(int i = 0; i < STM32F4_TIMER_MAX_CALLBACK_COUNT; ++i) {
            if(tim9_callbacks[i])
                tim9_callbacks[i]();
        }

        handle.device = STM32F4_TIMER_9;
        stm32f4_timerClearIRQPending(&handle, TIMER_IRQ_UPDATE);    // TODO: check if overcapture flag is on.
    }
}

void TIM1_UP_TIM10_IRQHandler()
{
}

void TIM1_TRG_COM_TIM11_IRQHandler()
{
}

void TIM1_CC_IRQHandler()
{
}

void TIM2_IRQHandler()
{
    for(int i = 0; i < STM32F4_TIMER_MAX_CALLBACK_COUNT; ++i) {
        if(tim2_callbacks[i])
            tim2_callbacks[i]();
    }

    TimerHandle_t handle;
    handle.device = STM32F4_TIMER_2;
    stm32f4_timerClearIRQPending(&handle, TIMER_IRQ_UPDATE);
}

void TIM3_IRQHandler()
{
    for(int i = 0; i < STM32F4_TIMER_MAX_CALLBACK_COUNT; ++i) {
        if(tim3_callbacks[i])
            tim3_callbacks[i]();
    }

    TimerHandle_t handle;
    handle.device = STM32F4_TIMER_3;
    stm32f4_timerClearIRQPending(&handle, TIMER_IRQ_UPDATE);
}

void TIM4_IRQHandler()
{
    for(int i = 0; i < STM32F4_TIMER_MAX_CALLBACK_COUNT; ++i) {
        if(tim4_callbacks[i])
            tim4_callbacks[i]();
    }

    TimerHandle_t handle;
    handle.device = STM32F4_TIMER_4;
    stm32f4_timerClearIRQPending(&handle, TIMER_IRQ_UPDATE);
}

void TIM8_BRK_TIM12_IRQHandler()
{
}

void TIM8_UP_TIM13_IRQHandler()
{
}

void TIM8_TRG_COM_TIM14_IRQHandler()
{
}

void TIM8_CC_IRQHandler()
{
}

void TIM5_IRQHandler()
{
    for(int i = 0; i < STM32F4_TIMER_MAX_CALLBACK_COUNT; ++i) {
        if(tim5_callbacks[i])
            tim5_callbacks[i]();
    }

    TimerHandle_t handle;
    handle.device = STM32F4_TIMER_5;
    stm32f4_timerClearIRQPending(&handle, TIMER_IRQ_UPDATE);
}

void TIM6_DAC_IRQHandler()
{
}

void TIM7_IRQHandler()
{
    for(int i = 0; i < STM32F4_TIMER_MAX_CALLBACK_COUNT; ++i) {
        if(tim7_callbacks[i])
            tim7_callbacks[i]();
    }

    TimerHandle_t handle;
    handle.device = STM32F4_TIMER_7;
    stm32f4_timerClearIRQPending(&handle, TIMER_IRQ_UPDATE);
}

//---------------------------------------------------------------------------------------------------------------
// INTERFACE FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

uint8_t stm32f4_timerToIRQChannel(TimerHandle_t *handle, STM32F4_TimerIRQSource_t irq_source)
{
    switch(handle->device) {
    case STM32F4_TIMER_1: {
        switch(irq_source) {
        case TIMER_IRQ_BREAK:               return TIM1_BRK_TIM9_IRQn;
        case TIMER_IRQ_UPDATE:              return TIM1_UP_TIM10_IRQn;
        case TIMER_IRQ_COM:                 // Fall through
        case TIMER_IRQ_TRIGGER:             return TIM1_TRG_COM_TIM11_IRQn;
        case TIMER_IRQ_CAPTURE_COMPARE_1:   // Fall through
        case TIMER_IRQ_CAPTURE_COMPARE_2:   // Fall through
        case TIMER_IRQ_CAPTURE_COMPARE_3:   // Fall through
        case TIMER_IRQ_CAPTURE_COMPARE_4:   return TIM1_CC_IRQn;
        }
    }
    case STM32F4_TIMER_2:   return TIM2_IRQn;
    case STM32F4_TIMER_3:   return TIM3_IRQn;
    case STM32F4_TIMER_4:   return TIM4_IRQn;
    case STM32F4_TIMER_5:   return TIM5_IRQn;
    case STM32F4_TIMER_6:   return TIM6_DAC_IRQn;
    case STM32F4_TIMER_7:   return TIM7_IRQn;
    case STM32F4_TIMER_8: {
        switch(irq_source) {
        case TIMER_IRQ_BREAK:               return TIM8_BRK_TIM12_IRQn;
        case TIMER_IRQ_UPDATE:              return TIM8_UP_TIM13_IRQn;
        case TIMER_IRQ_COM:                 // Fall through
        case TIMER_IRQ_TRIGGER:             return TIM8_TRG_COM_TIM14_IRQn;
        case TIMER_IRQ_CAPTURE_COMPARE_1:   // Fall through
        case TIMER_IRQ_CAPTURE_COMPARE_2:   // Fall through
        case TIMER_IRQ_CAPTURE_COMPARE_3:   // Fall through
        case TIMER_IRQ_CAPTURE_COMPARE_4:   return TIM8_CC_IRQn;
        }

    }
    case STM32F4_TIMER_9:   return TIM1_BRK_TIM9_IRQn;
    case STM32F4_TIMER_10:  return TIM1_UP_TIM10_IRQn;
    case STM32F4_TIMER_11:  return TIM1_TRG_COM_TIM11_IRQn;
    case STM32F4_TIMER_12:  return TIM8_BRK_TIM12_IRQn;
    case STM32F4_TIMER_13:  return TIM8_UP_TIM13_IRQn;
    case STM32F4_TIMER_14:  return TIM8_TRG_COM_TIM14_IRQn;
    }

    return 0;
}

bool stm32f4_registerEventCallback(TimerHandle_t *handle, STM32F4_TimerIRQSource_t irq_source, TimerEventCallback_t callback)
{
    TimerEventCallback_t *callback_set = NULL;

    switch(handle->device) {
    case STM32F4_TIMER_1: {
        switch(irq_source) {
        case TIMER_IRQ_BREAK:               callback_set = tim1_brk_callbacks; break;
        case TIMER_IRQ_UPDATE:              callback_set = tim1_up_callbacks; break;
        case TIMER_IRQ_COM:                 callback_set = tim1_com_callbacks; break;
        case TIMER_IRQ_TRIGGER:             callback_set = tim1_trig_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_1:   callback_set = tim1_cc1_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_2:   callback_set = tim1_cc2_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_3:   callback_set = tim1_cc3_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_4:   callback_set = tim1_cc4_callbacks; break;
        }
        break;
    }
    case STM32F4_TIMER_2:   callback_set = tim2_callbacks; break;
    case STM32F4_TIMER_3:   callback_set = tim3_callbacks; break;
    case STM32F4_TIMER_4:   callback_set = tim4_callbacks; break;
    case STM32F4_TIMER_5:   callback_set = tim5_callbacks; break;
    case STM32F4_TIMER_6:   callback_set = tim6_callbacks; break;
    case STM32F4_TIMER_7:   callback_set = tim7_callbacks; break;
    case STM32F4_TIMER_8: {
        switch(irq_source) {
        case TIMER_IRQ_BREAK:               callback_set = tim8_brk_callbacks; break;
        case TIMER_IRQ_UPDATE:              callback_set = tim8_up_callbacks; break;
        case TIMER_IRQ_COM:                 callback_set = tim8_com_callbacks; break;
        case TIMER_IRQ_TRIGGER:             callback_set = tim8_trig_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_1:   callback_set = tim8_cc1_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_2:   callback_set = tim8_cc2_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_3:   callback_set = tim8_cc3_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_4:   callback_set = tim8_cc4_callbacks; break;
        }
        break;
    }
    case STM32F4_TIMER_9:   callback_set = tim9_callbacks; break;
    case STM32F4_TIMER_10:  callback_set = tim10_callbacks; break;
    case STM32F4_TIMER_11:  callback_set = tim11_callbacks; break;
    case STM32F4_TIMER_12:  callback_set = tim12_callbacks; break;
    case STM32F4_TIMER_13:  callback_set = tim13_callbacks; break;
    case STM32F4_TIMER_14:  callback_set = tim14_callbacks; break;
    default:                return false;
    }

    bool status = stm32f4_timerAddCallback(callback_set, callback);
    stm32f4_timerEnableIRQ(handle, irq_source, true);

    return status;
}

bool stm32f4_unregisterEventCallback(TimerHandle_t *handle, STM32F4_TimerIRQSource_t irq_source, TimerEventCallback_t callback)
{
    TimerEventCallback_t *callback_set = NULL;

    switch(handle->device) {
    case STM32F4_TIMER_1: {
        switch(irq_source) {
        case TIMER_IRQ_BREAK:               callback_set = tim1_brk_callbacks; break;
        case TIMER_IRQ_UPDATE:              callback_set = tim1_up_callbacks; break;
        case TIMER_IRQ_COM:                 callback_set = tim1_com_callbacks; break;
        case TIMER_IRQ_TRIGGER:             callback_set = tim1_trig_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_1:   callback_set = tim1_cc1_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_2:   callback_set = tim1_cc2_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_3:   callback_set = tim1_cc3_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_4:   callback_set = tim1_cc4_callbacks; break;
        }
        break;
    }
    case STM32F4_TIMER_2:   callback_set = tim2_callbacks; break;
    case STM32F4_TIMER_3:   callback_set = tim3_callbacks; break;
    case STM32F4_TIMER_4:   callback_set = tim4_callbacks; break;
    case STM32F4_TIMER_5:   callback_set = tim5_callbacks; break;
    case STM32F4_TIMER_6:   callback_set = tim6_callbacks; break;
    case STM32F4_TIMER_7:   callback_set = tim7_callbacks; break;
    case STM32F4_TIMER_8: {
        switch(irq_source) {
        case TIMER_IRQ_BREAK:               callback_set = tim8_brk_callbacks; break;
        case TIMER_IRQ_UPDATE:              callback_set = tim8_up_callbacks; break;
        case TIMER_IRQ_COM:                 callback_set = tim8_com_callbacks; break;
        case TIMER_IRQ_TRIGGER:             callback_set = tim8_trig_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_1:   callback_set = tim8_cc1_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_2:   callback_set = tim8_cc2_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_3:   callback_set = tim8_cc3_callbacks; break;
        case TIMER_IRQ_CAPTURE_COMPARE_4:   callback_set = tim8_cc4_callbacks; break;
        }
        break;
    }
    case STM32F4_TIMER_9:   callback_set = tim9_callbacks; break;
    case STM32F4_TIMER_10:  callback_set = tim10_callbacks; break;
    case STM32F4_TIMER_11:  callback_set = tim11_callbacks; break;
    case STM32F4_TIMER_12:  callback_set = tim12_callbacks; break;
    case STM32F4_TIMER_13:  callback_set = tim13_callbacks; break;
    case STM32F4_TIMER_14:  callback_set = tim14_callbacks; break;
    default:                return false;
    }

    int used_slots = STM32F4_TIMER_MAX_CALLBACK_COUNT;
    bool status = stm32f4_timerRemoveCallback(callback_set, callback, &used_slots);
    if(used_slots == 0)
        stm32f4_timerEnableIRQ(handle, irq_source, false);

    return status;
}
