//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_timer.h
// Author     : Kuba Sejdak
// Created on : 05.09.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef STM32F4_TIMER_H
#define STM32F4_TIMER_H

#include "hal/timer.h"

#include <stdint.h>

typedef uint16_t STM32F4_Prescaler_t;

// Timer device.
#define STM32F4_TIMER_1     1
#define STM32F4_TIMER_2     2
#define STM32F4_TIMER_3     3
#define STM32F4_TIMER_4     4
#define STM32F4_TIMER_5     5
#define STM32F4_TIMER_6     6
#define STM32F4_TIMER_7     7
#define STM32F4_TIMER_8     8
#define STM32F4_TIMER_9     9
#define STM32F4_TIMER_10    10
#define STM32F4_TIMER_11    11
#define STM32F4_TIMER_12    12
#define STM32F4_TIMER_13    13
#define STM32F4_TIMER_14    14

// Timer counter mode.
typedef enum
{
    COUNTER_MODE_UP               = 0x00,
    COUNTER_MODE_DOWN             = 0x10,
    COUNTER_MODE_CENTER_ALIGNED_1 = 0x20,
    COUNTER_MODE_CENTER_ALIGNED_2 = 0x40,
    COUNTER_MODE_CENTER_ALIGNED_3 = 0x60
} STM32F4_CounterMode_t;

// Timer clock division.
typedef enum
{
    CLOCK_DIVISION_1 = 0x000,
    CLOCK_DIVISION_2 = 0x100,
    CLOCK_DIVISION_3 = 0x200
} STM32F4_ClockDivision_t;

// Timer prescaler reload mode.
typedef enum
{
    PRESCALER_RELOAD_MODE_UPDATE    = 0x0,
    PRESCALER_RELOAD_MODE_IMMEDIATE = 0x1
} STM32F4_PrescalerReloadMode_t;

// Timer config structure.
typedef struct
{
    STM32F4_Prescaler_t prescaler;
    STM32F4_CounterMode_t counter_mode;
    uint16_t period;
    STM32F4_ClockDivision_t clock_division;
    uint8_t repetition_counter;                 // Only for TIM1 and TIM8.
} STM32F4_TimerConfig_t;

// Timer output compare mode.
typedef enum
{
    OUTPUT_COMPARE_MODE_TIMING   = 0x00,
    OUTPUT_COMPARE_MODE_ACTIVE   = 0x10,
    OUTPUT_COMPARE_MODE_INACTIVE = 0x20,
    OUTPUT_COMPARE_MODE_TOGGLE   = 0x30,
    OUTPUT_COMPARE_MODE_PWM1     = 0x60,
    OUTPUT_COMPARE_MODE_PWM2     = 0x70
} STM32F4_OutputCompareMode_t;

// Timer output compare state.
typedef enum
{
    OUTPUT_COMPARE_STATE_DISABLE = 0x0,
    OUTPUT_COMPARE_STATE_ENABLE  = 0x1
} STM32F4_OutputCompareState_t;

// Timer output compare n state.
typedef enum
{
    OUTPUT_COMPARE_N_STATE_DISABLE = 0x0,
    OUTPUT_COMPARE_N_STATE_ENABLE  = 0x4
} STM32F4_OutputCompareNState_t;

// Timer output compare polarity.
typedef enum
{
    OUTPUT_COMPARE_POLARITY_HIGH = 0x0,
    OUTPUT_COMPARE_POLARITY_LOW  = 0x2
} STM32F4_OutputComparePolarity_t;

// Timer output compare n polarity.
typedef enum
{
    OUTPUT_COMPARE_N_POLARITY_HIGH = 0x0,
    OUTPUT_COMPARE_N_POLARITY_LOW  = 0x8
} STM32F4_OutputCompareNPolarity_t;

// Timer output compare idle state.
typedef enum
{
    OUTPUT_COMPARE_IDLE_STATE_SET   = 0x100,
    OUTPUT_COMPARE_IDLE_STATE_RESET = 0x000
} STM32F4_IdleState_t;

// Timer output compare n idle state.
typedef enum
{
    OUTPUT_COMPARE_N_IDLE_STATE_SET   = 0x200,
    OUTPUT_COMPARE_N_IDLE_STATE_RESET = 0x000
} STM32F4_NIdleState_t;

// Timer output compare config structure.
typedef struct
{
    STM32F4_OutputCompareMode_t mode;
    STM32F4_OutputCompareState_t output_state;
    STM32F4_OutputCompareNState_t output_n_state;   // Only for TIM1 and TIM8.
    uint16_t pulse;
    STM32F4_OutputComparePolarity_t polarity;
    STM32F4_OutputCompareNPolarity_t n_polarity;    // Only for TIM1 and TIM8.
    STM32F4_IdleState_t idle_state;                 // Only for TIM1 and TIM8.
    STM32F4_NIdleState_t n_idle_state;              // Only for TIM1 and TIM8.
} STM32F4_OutputCompareConfig_t;

// Timer output compare preload state.
typedef enum
{
    OUTPUT_COMPARE_PRELOAD_ENABLE  = 0x8,
    OUTPUT_COMPARE_PRELOAD_DISABLE = 0x0
} STM32F4_OutputComparePreloadState_t;

bool stm32f4_timerInit(TimerDevice_t device, STM32F4_TimerConfig_t config);

bool stm32f4_outputCompareInit(TimerDevice_t device, uint32_t channel, STM32F4_OutputCompareConfig_t config);
bool stm32f4_outputCompareChannel1Init(TimerDevice_t device, STM32F4_OutputCompareConfig_t config);
bool stm32f4_outputCompareChannel2Init(TimerDevice_t device, STM32F4_OutputCompareConfig_t config);
bool stm32f4_outputCompareChannel3Init(TimerDevice_t device, STM32F4_OutputCompareConfig_t config);
bool stm32f4_outputCompareChannel4Init(TimerDevice_t device, STM32F4_OutputCompareConfig_t config);

void stm32f4_outputComparePreloadConfig(TimerDevice_t device, uint32_t channel, STM32F4_OutputComparePreloadState_t preload_state);
void stm32f4_outputComparePreload1Config(TimerDevice_t device, STM32F4_OutputComparePreloadState_t preload_state);
void stm32f4_outputComparePreload2Config(TimerDevice_t device, STM32F4_OutputComparePreloadState_t preload_state);
void stm32f4_outputComparePreload3Config(TimerDevice_t device, STM32F4_OutputComparePreloadState_t preload_state);
void stm32f4_outputComparePreload4Config(TimerDevice_t device, STM32F4_OutputComparePreloadState_t preload_state);

#endif
