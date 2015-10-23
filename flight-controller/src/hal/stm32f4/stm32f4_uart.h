//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_uart.h
// Author     : Kuba Sejdak
// Created on : 11.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef STM32F4_UART_H
#define STM32F4_UART_H

#include "hal/uart.h"

// UART device.
#define STM32F4_USART_1     1
#define STM32F4_USART_2     2
#define STM32F4_USART_3     3
#define STM32F4_UART_4      4
#define STM32F4_UART_5      5
#define STM32F4_USART_6     6

// UART clock enabled.
typedef enum {
    UART_CLOCK_DISABLED = 0x000,
    UART_CLOCK_ENABLED  = 0x800
} STM32F4_UARTClockEnabled_t;

// UART clock polarity.
typedef enum {
    UART_CLOCK_POLARITY_LOW  = 0x000,
    UART_CLOCK_POLARITY_HIGH = 0x400
} STM32F4_UARTClockPolarity_t;

// UART clock phase.
typedef enum {
    UART_CLOCK_PHASE_1_TRANSITION = 0x000,
    UART_CLOCK_PHASE_2_TRANSITION = 0x200
} STM32F4_UARTClockPhase_t;

// UART clock last bit.
typedef enum {
    UART_CLOCK_LAST_BIT_DISABLED = 0x000,
    UART_CLOCK_LAST_BIT_ENABLED  = 0x100
} STM32F4_UARTClockLastBit_t;

// UART clock config structure.
typedef struct {
    STM32F4_UARTClockEnabled_t enabled;
    STM32F4_UARTClockPolarity_t polarity;
    STM32F4_UARTClockPhase_t phase;
    STM32F4_UARTClockLastBit_t last_bit;
} STM32F4_UARTClockConfig_t;

// UART config strucrure.
typedef struct {
    UARTConfig_t general_config;
    STM32F4_UARTClockConfig_t clock_config;
} STM32F4_UARTConfig_t;

bool stm32f4_uartInit(UARTHandle_t *handle, STM32F4_UARTConfig_t config);
void stm32f4_uartClockInit(UARTHandle_t *handle, STM32F4_UARTClockConfig_t clock_config);
int stm32f4_uartToPinFunction(UARTHandle_t *handle);

#endif
