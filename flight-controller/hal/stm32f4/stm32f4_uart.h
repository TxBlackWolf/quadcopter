////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.08.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef STM32F4_UART_H
#define STM32F4_UART_H

#include "hal/uart.h"
#include "stm32f4.h"
#include "CMSIS/stm32f4xx.h"

#include <stdbool.h>

typedef USART_TypeDef UART_t;

// UART device.
#define STM32F4_USART_1         1
#define STM32F4_USART_2         2
#define STM32F4_USART_3         3
#define STM32F4_UART_4          4
#define STM32F4_UART_5          5
#define STM32F4_USART_6         6

#define STM32F4_UART_COUNT      6

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

#define UART_IRQ_CR2_FLAG       0x01000
#define UART_IRQ_CR3_FLAG       0x10000

// UART interrupt source.
typedef enum {
    UART_IRQ_LINE_IDLE      = 0x00010,
    UART_IRQ_RXNE_OVERRUN   = 0x00020,
    UART_IRQ_TX_COMPLETE    = 0x00040,
    UART_IRQ_TX_EMPTY       = 0x00080,
    UART_IRQ_PARTITY_ERROR  = 0x00100,
    UART_IRQ_LINE_BREAK     = 0x01040,
    UART_IRQ_NOISE_FRAMING  = 0x01000,
    UART_IRQ_CTS_CHANGE     = 0x10400,      // Not available for UART4 and UART5.
    UART_IRQ_COUNT          = 8
} STM32F4_UARTIRQSource_t;

typedef struct {
    uint16_t irq_flags;
} STM32F4_UARTPrivateData_t;

extern STM32F4_UARTPrivateData_t uarts_privateData[STM32F4_UART_COUNT];

UART_t *stm32f4_uartGetRegisters(UARTDevice_t device);
bool stm32f4_uartInit(UARTHandle_t *handle, STM32F4_UARTConfig_t *config);
int stm32f4_uartToPinFunction(UARTHandle_t *handle);

uint8_t stm32f4_uartToIRQChannel(UARTHandle_t *handle);
uint16_t stm32f4_uartIRQToStatusFlag(STM32F4_UARTIRQSource_t irq_source);
void stm32f4_uartEnableIRQ(UARTHandle_t *handle, STM32F4_UARTIRQSource_t irq_source, bool enabled);
void stm32f4_uartClearIRQPending(UARTHandle_t *handle, STM32F4_UARTIRQSource_t irq_source);

bool stm32f4_uartRegisterCallback(UARTHandle_t *handle, STM32F4_UARTIRQSource_t irq_source, HALEventCallback_t callback);
bool stm32f4_uartUnregisterCallback(UARTHandle_t *handle, STM32F4_UARTIRQSource_t irq_source, HALEventCallback_t callback);

#endif
