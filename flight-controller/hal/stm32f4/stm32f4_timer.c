////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       05.09.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "stm32f4_timer.h"
#include "stm32f4_gpio_functions.h"
#include "stm32f4_rcc.h"

//=============================================================================================
// HELPER FUNCTIONS
//=============================================================================================

static void stm32f4_timerEnableClock(TimerDevice_t device, bool value)
{
    switch (device) {
    case STM32F4_TIMER_1:   stm32f4_rccEnablePeripheralClockAPB2(RCC_APB2_PERIPHERAL_TIM1, value);  break;
    case STM32F4_TIMER_2:   stm32f4_rccEnablePeripheralClockAPB1(RCC_APB1_PERIPHERAL_TIM2, value);  break;
    case STM32F4_TIMER_3:   stm32f4_rccEnablePeripheralClockAPB1(RCC_APB1_PERIPHERAL_TIM3, value);  break;
    case STM32F4_TIMER_4:   stm32f4_rccEnablePeripheralClockAPB1(RCC_APB1_PERIPHERAL_TIM4, value);  break;
    case STM32F4_TIMER_5:   stm32f4_rccEnablePeripheralClockAPB1(RCC_APB1_PERIPHERAL_TIM5, value);  break;
    case STM32F4_TIMER_6:   stm32f4_rccEnablePeripheralClockAPB1(RCC_APB1_PERIPHERAL_TIM6, value);  break;
    case STM32F4_TIMER_7:   stm32f4_rccEnablePeripheralClockAPB1(RCC_APB1_PERIPHERAL_TIM7, value);  break;
    case STM32F4_TIMER_8:   stm32f4_rccEnablePeripheralClockAPB2(RCC_APB2_PERIPHERAL_TIM8, value);  break;
    case STM32F4_TIMER_9:   stm32f4_rccEnablePeripheralClockAPB2(RCC_APB2_PERIPHERAL_TIM9, value);  break;
    case STM32F4_TIMER_10:  stm32f4_rccEnablePeripheralClockAPB2(RCC_APB2_PERIPHERAL_TIM10, value); break;
    case STM32F4_TIMER_11:  stm32f4_rccEnablePeripheralClockAPB2(RCC_APB2_PERIPHERAL_TIM11, value); break;
    case STM32F4_TIMER_12:  stm32f4_rccEnablePeripheralClockAPB1(RCC_APB1_PERIPHERAL_TIM12, value); break;
    case STM32F4_TIMER_13:  stm32f4_rccEnablePeripheralClockAPB1(RCC_APB1_PERIPHERAL_TIM13, value); break;
    case STM32F4_TIMER_14:  stm32f4_rccEnablePeripheralClockAPB1(RCC_APB1_PERIPHERAL_TIM14, value); break;
    }
}

//=============================================================================================
// INTERFACE FUNCTIONS
//=============================================================================================

Timer_t *stm32f4_timerGetRegisters(TimerDevice_t device)
{
    switch (device) {
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

bool stm32f4_timerInit(TimerHandle_t *handle, STM32F4_TimerConfig_t *config)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    stm32f4_timerEnableClock(handle->device, true);

    if ((timer == TIM1) || (timer == TIM8) || (timer == TIM2) || (timer == TIM3) || (timer == TIM4) || (timer == TIM5))
        timer->CR1 |= config->counter_mode;

    if ((timer != TIM6) && (timer != TIM7))
        timer->CR1 |= config->clock_division;

    timer->ARR = config->period;
    timer->PSC = config->prescaler;

    if ((timer == TIM1) || (timer == TIM8))
        timer->RCR = config->repetition_counter;

    timer->EGR = PRESCALER_RELOAD_MODE_IMMEDIATE;
    return true;
}

int stm32f4_timerToPinFunction(TimerHandle_t *handle)
{
    switch (handle->device) {
    case STM32F4_TIMER_1:   return GPIO_AF_TIM1;
    case STM32F4_TIMER_2:   return GPIO_AF_TIM2;
    case STM32F4_TIMER_3:   return GPIO_AF_TIM3;
    case STM32F4_TIMER_4:   return GPIO_AF_TIM4;
    case STM32F4_TIMER_5:   return GPIO_AF_TIM5;
    case STM32F4_TIMER_6:   return -1;
    case STM32F4_TIMER_7:   return -1;
    case STM32F4_TIMER_8:   return GPIO_AF_TIM8;
    case STM32F4_TIMER_9:   return GPIO_AF_TIM9;
    case STM32F4_TIMER_10:  return GPIO_AF_TIM10;
    case STM32F4_TIMER_11:  return GPIO_AF_TIM11;
    case STM32F4_TIMER_12:  return GPIO_AF_TIM12;
    case STM32F4_TIMER_13:  return GPIO_AF_TIM13;
    case STM32F4_TIMER_14:  return GPIO_AF_TIM14;
    }

    return -1;
}

bool stm32f4_timerSetPeriodConfig(TimerHandle_t *handle, float period_ms, STM32F4_TimerConfig_t *config)
{
    STM32F4_ClockFrequencies_t sys_freqs;
    stm32f4_rccGetClocksFrequencies(&sys_freqs);

    // Timers have internal PLLs, that double bus frequency.
    uint32_t base_freq_hz = 0;
    switch (handle->device) {
    // APB1 bus.
    case STM32F4_TIMER_2:
    case STM32F4_TIMER_3:
    case STM32F4_TIMER_4:
    case STM32F4_TIMER_5:
    case STM32F4_TIMER_6:
    case STM32F4_TIMER_7:
    case STM32F4_TIMER_12:
    case STM32F4_TIMER_13:
    case STM32F4_TIMER_14:
        base_freq_hz = sys_freqs.pclk1_frequency_hz * 2;
        break;

    // APB2 bus.
    case STM32F4_TIMER_1:
    case STM32F4_TIMER_8:
    case STM32F4_TIMER_9:
    case STM32F4_TIMER_10:
    case STM32F4_TIMER_11:
        base_freq_hz = sys_freqs.pclk2_frequency_hz * 2;
        break;
    }

    // Find appropriate prescaler to match demanded period.
    uint16_t prescaler = 0;
    float timer_freq_hz = 0.0f;
    float timer_period_ms = 0.0f;

    for (prescaler = 0; prescaler != UINT16_MAX; ++prescaler) {
        // Add 1, because this is what MCU will do (and avoid dividing by 0);
        timer_freq_hz = base_freq_hz / (prescaler + 1);
        timer_period_ms = (UINT16_MAX / timer_freq_hz) * 1000;
        if (timer_period_ms >= period_ms)
            break;

        if (prescaler + 1 == UINT16_MAX)
            return false;
    }
    config->prescaler = prescaler;

    // Find approproate counter to match demanded period.
    config->period = (UINT16_MAX * period_ms) / timer_period_ms;

    return true;
}

bool stm32f4_outputCompareInit(TimerHandle_t *handle, STM32F4_OutputCompareConfig_t *config)
{
    switch (handle->channel) {
    case 1:     return stm32f4_outputCompareChannel1Init(handle, config);
    case 2:     return stm32f4_outputCompareChannel2Init(handle, config);
    case 3:     return stm32f4_outputCompareChannel3Init(handle, config);
    case 4:     return stm32f4_outputCompareChannel4Init(handle, config);
    }

    return false;
}

bool stm32f4_outputCompareChannel1Init(TimerHandle_t *handle, STM32F4_OutputCompareConfig_t *config)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    if (timer == TIM6 || timer == TIM7)
        return false;

    // Disable channel 1.
    timer->CCER &= ~TIM_CCER_CC1E;

    timer->CCMR1 |= config->mode;
    timer->CCER |= config->polarity;
    timer->CCER |= config->output_state;

    if (timer == TIM1 || timer == TIM8) {
        timer->CCER |= config->n_polarity;
        timer->CCER |= config->output_n_state;
        timer->CCR2 |= config->idle_state;
        timer->CCR2 |= config->n_idle_state;
    }

    timer->CCR1 = config->pulse;

    return true;
}

bool stm32f4_outputCompareChannel2Init(TimerHandle_t *handle, STM32F4_OutputCompareConfig_t *config)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    if (timer == TIM6 || timer == TIM7 || timer == TIM10 || timer == TIM11 || timer == TIM13 || timer == TIM14)
        return false;

    // Disable channel 2.
    timer->CCER &= ~TIM_CCER_CC2E;

    timer->CCMR1 |= (config->mode << 8);
    timer->CCER |= (config->polarity << 4);
    timer->CCER |= (config->output_state << 4);

    if (timer == TIM1 || timer == TIM8) {
        timer->CCER |= (config->n_polarity << 4);
        timer->CCER |= (config->output_n_state << 4);
        timer->CCR2 |= (config->idle_state << 2);
        timer->CCR2 |= (config->n_idle_state << 2);
    }

    timer->CCR2 = config->pulse;

    return true;
}

bool stm32f4_outputCompareChannel3Init(TimerHandle_t *handle, STM32F4_OutputCompareConfig_t *config)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    if (timer == TIM6 || timer == TIM7 || timer == TIM9 || timer == TIM10 || timer == TIM11 || timer == TIM12 || timer == TIM13 || timer == TIM14)
        return false;

    // Disable channel 3.
    timer->CCER &= ~TIM_CCER_CC3E;

    timer->CCMR2 |= config->mode;
    timer->CCER |= (config->polarity << 8);
    timer->CCER |= (config->output_state << 8);

    if (timer == TIM1 || timer == TIM8) {
        timer->CCER |= (config->n_polarity << 8);
        timer->CCER |= (config->output_n_state << 8);
        timer->CCR2 |= (config->idle_state << 4);
        timer->CCR2 |= (config->n_idle_state << 4);
    }

    timer->CCR3 = config->pulse;

    return true;
}

bool stm32f4_outputCompareChannel4Init(TimerHandle_t *handle, STM32F4_OutputCompareConfig_t *config)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    if (timer == TIM6 || timer == TIM7 || timer == TIM9 || timer == TIM10 || timer == TIM11 || timer == TIM12 || timer == TIM13 || timer == TIM14)
        return false;

    // Disable channel 4.
    timer->CCER &= ~TIM_CCER_CC4E;

    timer->CCMR2 |= (config->mode << 8);
    timer->CCER |= (config->polarity << 12);
    timer->CCER |= (config->output_state << 12);

    if (timer == TIM1 || timer == TIM8)
        timer->CCR2 |= (config->idle_state << 6);

    timer->CCR4 = config->pulse;

    return true;
}

void stm32f4_outputComparePreloadConfig(TimerHandle_t *handle, STM32F4_OutputComparePreloadState_t preload_state)
{
    switch (handle->channel) {
    case 1:     stm32f4_outputComparePreload1Config(handle, preload_state); break;
    case 2:     stm32f4_outputComparePreload2Config(handle, preload_state); break;
    case 3:     stm32f4_outputComparePreload3Config(handle, preload_state); break;
    case 4:     stm32f4_outputComparePreload4Config(handle, preload_state); break;
    }
}

void stm32f4_outputComparePreload1Config(TimerHandle_t *handle, STM32F4_OutputComparePreloadState_t preload_state)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    if (timer == TIM6 || timer == TIM7)
        return;

    timer->CCMR1 |= preload_state;
}

void stm32f4_outputComparePreload2Config(TimerHandle_t *handle, STM32F4_OutputComparePreloadState_t preload_state)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    if (timer == TIM6 || timer == TIM7 || timer == TIM10 || timer == TIM11 || timer == TIM13 || timer == TIM14)
        return;

    timer->CCMR1 |= (preload_state << 8);
}

void stm32f4_outputComparePreload3Config(TimerHandle_t *handle, STM32F4_OutputComparePreloadState_t preload_state)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    if (timer == TIM6 || timer == TIM7 || timer == TIM9 || timer == TIM10 || timer == TIM11 || timer == TIM12 || timer == TIM13 || timer == TIM14)
        return;

    timer->CCMR2 |= preload_state;
}

void stm32f4_outputComparePreload4Config(TimerHandle_t *handle, STM32F4_OutputComparePreloadState_t preload_state)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    if (timer == TIM6 || timer == TIM7 || timer == TIM9 || timer == TIM10 || timer == TIM11 || timer == TIM12 || timer == TIM13 || timer == TIM14)
        return;

    timer->CCMR2 |= (preload_state << 8);
}

uint16_t stm32f4_getOutputComparePeriod(TimerHandle_t *handle)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    return timer->ARR;
}

void stm32f4_setOutputComparePulse(TimerHandle_t *handle, uint16_t pulse)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);

    switch (handle->channel) {
    case 1:     timer->CCR1 = pulse; break;
    case 2:     timer->CCR2 = pulse; break;
    case 3:     timer->CCR3 = pulse; break;
    case 4:     timer->CCR4 = pulse; break;
    }
}

void stm32f4_timerEnableIRQ(TimerHandle_t *handle, STM32F4_TimerIRQSource_t irq_source, bool enabled)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    if (enabled)
        timer->DIER |= irq_source;
    else
        timer->DIER &= ~irq_source;
}

void stm32f4_timerClearIRQPending(TimerHandle_t *handle, STM32F4_TimerIRQSource_t irq_source)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    timer->SR &= ~irq_source;
}

void timer_activate(TimerHandle_t *handle)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    timer->CR1 |= TIM_CR1_CEN;
}

void timer_deactivate(TimerHandle_t *handle)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    timer->CR1 &= ~TIM_CR1_CEN;
}

void timer_setEventFrequency(TimerHandle_t *handle, TimerConfig_t config)
{
    timer_deactivate(handle);

    float period_ms = config.use_period ? config.period_ms : ((1.0f / config.frequency_hz) * 1000);
    STM32F4_TimerConfig_t timer_config;
    stm32f4_timerSetPeriodConfig(handle, period_ms, &timer_config);

    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    timer->ARR = timer_config.period;
    timer->PSC = timer_config.prescaler;

    timer_activate(handle);
}

uint32_t timer_getCounter(TimerHandle_t *handle)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    return timer->CNT;
}

void timer_setCounter(TimerHandle_t *handle, uint32_t value)
{
    Timer_t *timer = stm32f4_timerGetRegisters(handle->device);
    timer->CNT = value;
}
