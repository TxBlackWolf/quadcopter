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
#include "board/console.h"

#include <stdlib.h>

#define STM32F4_TIMER_MAX_CALLBACK_COUNT    5

TimerEventCallback_t tim1_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
TimerEventCallback_t tim2_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
TimerEventCallback_t tim3_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
TimerEventCallback_t tim4_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
TimerEventCallback_t tim5_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
TimerEventCallback_t tim6_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
TimerEventCallback_t tim7_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
TimerEventCallback_t tim8_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
TimerEventCallback_t tim9_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
TimerEventCallback_t tim10_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
TimerEventCallback_t tim11_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
TimerEventCallback_t tim12_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
TimerEventCallback_t tim13_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];
TimerEventCallback_t tim14_callbacks[STM32F4_TIMER_MAX_CALLBACK_COUNT];

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

bool stm32f4_timerRemoveCallback(TimerEventCallback_t *callback_set, TimerEventCallback_t callback)
{
    for(int i = 0; i < STM32F4_TIMER_MAX_CALLBACK_COUNT; ++i) {
        if(callback_set[i] != callback)
            continue;

        callback_set[i] = NULL;
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------------------------------------------
// TIMER INTERRUPT HANDLERS
//---------------------------------------------------------------------------------------------------------------

void TIM1_BRK_TIM9_IRQHandler()
{
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
}

void TIM3_IRQHandler()
{
}

void TIM4_IRQHandler()
{
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
}

void TIM6_DAC_IRQHandler()
{
}

void TIM7_IRQHandler()
{
}

//---------------------------------------------------------------------------------------------------------------
// INTERFACE FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

bool timer_registerEventCallback(TimerHandle_t *handle, TimerEventCallback_t callback)
{
    switch(handle->device) {
    case STM32F4_TIMER_1:   return stm32f4_timerAddCallback(tim1_callbacks, callback);
    case STM32F4_TIMER_2:   return stm32f4_timerAddCallback(tim2_callbacks, callback);
    case STM32F4_TIMER_3:   return stm32f4_timerAddCallback(tim3_callbacks, callback);
    case STM32F4_TIMER_4:   return stm32f4_timerAddCallback(tim4_callbacks, callback);
    case STM32F4_TIMER_5:   return stm32f4_timerAddCallback(tim5_callbacks, callback);
    case STM32F4_TIMER_6:   return stm32f4_timerAddCallback(tim6_callbacks, callback);
    case STM32F4_TIMER_7:   return stm32f4_timerAddCallback(tim7_callbacks, callback);
    case STM32F4_TIMER_8:   return stm32f4_timerAddCallback(tim8_callbacks, callback);
    case STM32F4_TIMER_9:   return stm32f4_timerAddCallback(tim9_callbacks, callback);
    case STM32F4_TIMER_10:  return stm32f4_timerAddCallback(tim10_callbacks, callback);
    case STM32F4_TIMER_11:  return stm32f4_timerAddCallback(tim11_callbacks, callback);
    case STM32F4_TIMER_12:  return stm32f4_timerAddCallback(tim12_callbacks, callback);
    case STM32F4_TIMER_13:  return stm32f4_timerAddCallback(tim13_callbacks, callback);
    case STM32F4_TIMER_14:  return stm32f4_timerAddCallback(tim14_callbacks, callback);
    }

    return false;
}
