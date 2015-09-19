//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_timer.c
// Author     : Kuba Sejdak
// Created on : 05.09.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "stm32f4_timer.h"
#include "CMSIS/stm32f4xx.h"

typedef TIM_TypeDef Timer_t;

//---------------------------------------------------------------------------------------------------------------
// HELPER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

Timer_t *stm32f4_timerGetRegisters(TimerDevice_t device)
{
    switch(device)
    {
    case STM32F4_TIMER_1:   return TIM1;
    case STM32F4_TIMER_2:   return TIM2;
    case STM32F4_TIMER_3:   return TIM3;
    case STM32F4_TIMER_4:   return TIM4;
    case STM32F4_TIMER_5:   return TIM5;
    case STM32F4_TIMER_6:   return TIM6;
    case STM32F4_TIMER_7:   return TIM7;
    case STM32F4_TIMER_8:   return TIM8;
    case STM32F4_TIMER_9:   return TIM9;
    case STM32F4_TIMER_10:  return TIM10;
    case STM32F4_TIMER_11:  return TIM11;
    case STM32F4_TIMER_12:  return TIM12;
    case STM32F4_TIMER_13:  return TIM13;
    case STM32F4_TIMER_14:  return TIM14;
    }

    return 0;
}

//---------------------------------------------------------------------------------------------------------------
// INTERFACE FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

bool stm32f4_timerInit(TimerDevice_t device, STM32F4_TimerConfig_t config)
{
    Timer_t *timer = stm32f4_timerGetRegisters(device);

    if((timer == TIM1) || (timer == TIM8) || (timer == TIM2) || (timer == TIM3) || (timer == TIM4) || (timer == TIM5))
    {
        // Set counter mode.
        timer->CR1 |= config.counter_mode;
    }

    if((timer != TIM6) && (timer != TIM7))
    {
        // Set clock division.
        timer->CR1 |= config.clock_division;
    }

    // Set auto-reload value.
    timer->ARR = config.period;

    // Set prescaler.
    timer->PSC = config.prescaler;

    if((timer == TIM1) || (timer == TIM8))
    {
        // Set repetition counter.
        timer->RCR = config.repetition_counter;
    }

    timer->EGR = PRESCALER_RELOAD_MODE_IMMEDIATE;

    timer_activate(device);
    return true;
}

void timer_activate(TimerDevice_t device)
{
    Timer_t *timer = stm32f4_timerGetRegisters(device);
    timer->CR1 |= TIM_CR1_CEN;
}

void timer_deactivate(TimerDevice_t device)
{
    Timer_t *timer = stm32f4_timerGetRegisters(device);
    timer->CR1 &= ~TIM_CR1_CEN;
}

bool stm32f4_outputCompareInit(TimerDevice_t device, uint32_t channel, STM32F4_OutputCompareConfig_t config)
{
    switch(channel)
    {
    case 1:     return stm32f4_outputCompareChannel1Init(device, config);
    case 2:     return stm32f4_outputCompareChannel2Init(device, config);
    case 3:     return stm32f4_outputCompareChannel3Init(device, config);
    case 4:     return stm32f4_outputCompareChannel4Init(device, config);
    }

    return false;
}

bool stm32f4_outputCompareChannel1Init(TimerDevice_t device, STM32F4_OutputCompareConfig_t config)
{
    Timer_t *timer = stm32f4_timerGetRegisters(device);
    if(timer == TIM6 || timer == TIM7)
        return false;

    // Disable channel 1.
    timer->CCER &= ~TIM_CCER_CC1E;

    // Select output compare mode.
    timer->CCMR1 |= config.mode;

    // Set output compare polarity.
    timer->CCER |= config.polarity;

    // Set output state.
    timer->CCER |= config.output_state;

    if(timer == TIM1 || timer == TIM8)
    {
        // Set output n polarity.
        timer->CCER |= config.n_polarity;

        // Set output n state.
        timer->CCER |= config.output_n_state;

        // Set output idle state.
        timer->CCR2 |= config.idle_state;

        // Set output n idle state.
        timer->CCR2 |= config.n_idle_state;
    }

    // Set capture compare pulse.
    timer->CCR1 = config.pulse;

    return true;
}

bool stm32f4_outputCompareChannel2Init(TimerDevice_t device, STM32F4_OutputCompareConfig_t config)
{
    Timer_t *timer = stm32f4_timerGetRegisters(device);
    if(timer == TIM6 || timer == TIM7 || timer == TIM10 || timer == TIM11 || timer == TIM13 || timer == TIM14)
        return false;

    // Disable channel 2.
    timer->CCER &= ~TIM_CCER_CC2E;

    // Select output compare mode.
    timer->CCMR1 |= (config.mode << 8);

    // Set output compare polarity.
    timer->CCER |= (config.polarity << 4);

    // Set output state.
    timer->CCER |= (config.output_state << 4);

    if(timer == TIM1 || timer == TIM8)
    {
        // Set output n polarity.
        timer->CCER |= (config.n_polarity << 4);

        // Set output n state.
        timer->CCER |= (config.output_n_state << 4);

        // Set output idle state.
        timer->CCR2 |= (config.idle_state << 2);

        // Set output n idle state.
        timer->CCR2 |= (config.n_idle_state << 2);
    }

    // Set capture compare pulse.
    timer->CCR2 = config.pulse;

    return true;
}

bool stm32f4_outputCompareChannel3Init(TimerDevice_t device, STM32F4_OutputCompareConfig_t config)
{
    Timer_t *timer = stm32f4_timerGetRegisters(device);
    if(timer == TIM6 || timer == TIM7 || timer == TIM9 || timer == TIM10 || timer == TIM11 || timer == TIM12 || timer == TIM13 || timer == TIM14)
        return false;

    // Disable channel 3.
    timer->CCER &= ~TIM_CCER_CC3E;

    // Select output compare mode.
    timer->CCMR2 |= config.mode;

    // Set output compare polarity.
    timer->CCER |= (config.polarity << 8);

    // Set output state.
    timer->CCER |= (config.output_state << 8);

    if(timer == TIM1 || timer == TIM8)
    {
        // Set output n polarity.
        timer->CCER |= (config.n_polarity << 8);

        // Set output n state.
        timer->CCER |= (config.output_n_state << 8);

        // Set output idle state.
        timer->CCR2 |= (config.idle_state << 4);

        // Set output n idle state.
        timer->CCR2 |= (config.n_idle_state << 4);
    }

    // Set capture compare pulse.
    timer->CCR3 = config.pulse;

    return true;
}

bool stm32f4_outputCompareChannel4Init(TimerDevice_t device, STM32F4_OutputCompareConfig_t config)
{
    Timer_t *timer = stm32f4_timerGetRegisters(device);
    if(timer == TIM6 || timer == TIM7 || timer == TIM9 || timer == TIM10 || timer == TIM11 || timer == TIM12 || timer == TIM13 || timer == TIM14)
        return false;

    // Disable channel 4.
    timer->CCER &= ~TIM_CCER_CC4E;

    // Select output compare mode.
    timer->CCMR2 |= (config.mode << 8);

    // Set output compare polarity.
    timer->CCER |= (config.polarity << 12);

    // Set output state.
    timer->CCER |= (config.output_state << 12);

    if(timer == TIM1 || timer == TIM8)
    {
        // Set output idle state.
        timer->CCR2 |= (config.idle_state << 6);
    }

    // Set capture compare pulse.
    timer->CCR4 = config.pulse;

    return true;
}

void stm32f4_outputComparePreloadConfig(TimerDevice_t device, uint32_t channel, STM32F4_OutputComparePreloadState_t preload_state)
{
    switch(channel)
    {
    case 1:     return stm32f4_outputComparePreload1Config(device, preload_state);
    case 2:     return stm32f4_outputComparePreload2Config(device, preload_state);
    case 3:     return stm32f4_outputComparePreload3Config(device, preload_state);
    case 4:     return stm32f4_outputComparePreload4Config(device, preload_state);
    }

    return false;
}

void stm32f4_outputComparePreload1Config(TimerDevice_t device, STM32F4_OutputComparePreloadState_t preload_state)
{
    Timer_t *timer = stm32f4_timerGetRegisters(device);
    if(timer == TIM6 || timer == TIM7)
        return;

    timer->CCMR1 |= preload_state;
}

void stm32f4_outputComparePreload2Config(TimerDevice_t device, STM32F4_OutputComparePreloadState_t preload_state)
{
    Timer_t *timer = stm32f4_timerGetRegisters(device);
    if(timer == TIM6 || timer == TIM7 || timer == TIM10 || timer == TIM11 || timer == TIM13 || timer == TIM14)
        return;

    timer->CCMR1 |= (preload_state << 8);
}

void stm32f4_outputComparePreload3Config(TimerDevice_t device, STM32F4_OutputComparePreloadState_t preload_state)
{
    Timer_t *timer = stm32f4_timerGetRegisters(device);
    if(timer == TIM6 || timer == TIM7 || timer == TIM9 || timer == TIM10 || timer == TIM11 || timer == TIM12 || timer == TIM13 || timer == TIM14)
        return;

    timer->CCMR2 |= preload_state;
}

void stm32f4_outputComparePreload4Config(TimerDevice_t device, STM32F4_OutputComparePreloadState_t preload_state)
{
    Timer_t *timer = stm32f4_timerGetRegisters(device);
    if(timer == TIM6 || timer == TIM7 || timer == TIM9 || timer == TIM10 || timer == TIM11 || timer == TIM12 || timer == TIM13 || timer == TIM14)
        return;

    timer->CCMR2 |= (preload_state << 8);
}

uint32_t timer_getCounter(TimerDevice_t device)
{
    Timer_t *timer = stm32f4_timerGetRegisters(device);
    return timer->CNT;
}

void timer_setCounter(TimerDevice_t device, uint32_t value)
{
    Timer_t *timer = stm32f4_timerGetRegisters(device);
    timer->CNT = value;
}
