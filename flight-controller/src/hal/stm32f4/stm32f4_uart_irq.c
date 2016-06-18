////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       17.06.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "hal/uart.h"
#include "stm32f4.h"
#include "stm32f4xx.h"
#include "stm32f4_uart.h"

#include <stdio.h>

static HALEventCallback_t usart1_callbacks[UART_IRQ_COUNT][STM32F4_MAX_CALLBACK_COUNT];
static HALEventCallback_t usart2_callbacks[UART_IRQ_COUNT][STM32F4_MAX_CALLBACK_COUNT];
static HALEventCallback_t usart3_callbacks[UART_IRQ_COUNT][STM32F4_MAX_CALLBACK_COUNT];
static HALEventCallback_t uart4_callbacks[UART_IRQ_COUNT][STM32F4_MAX_CALLBACK_COUNT];
static HALEventCallback_t uart5_callbacks[UART_IRQ_COUNT][STM32F4_MAX_CALLBACK_COUNT];
static HALEventCallback_t usart6_callbacks[UART_IRQ_COUNT][STM32F4_MAX_CALLBACK_COUNT];

//=============================================================================================
// HELPER FUNCTIONS
//=============================================================================================

static int stm32f4_uartIRQToIndex(STM32F4_UARTIRQSource_t irq_source)
{
    switch (irq_source) {
    case UART_IRQ_LINE_IDLE:        return 0;
    case UART_IRQ_RXNE_OVERRUN:     return 1;
    case UART_IRQ_TX_COMPLETE:      return 2;
    case UART_IRQ_TX_EMPTY:         return 3;
    case UART_IRQ_PARTITY_ERROR:    return 4;
    case UART_IRQ_LINE_BREAK:       return 5;
    case UART_IRQ_NOISE_FRAMING:    return 6;
    case UART_IRQ_CTS_CHANGE:       return 7;
    default:                        break;
    }

    return -1;
}

static void stm32f4_uartHandleInterrupt(UARTHandle_t *handle, HALEventCallback_t callback_set[][STM32F4_MAX_CALLBACK_COUNT])
{
    UART_t *uart = stm32f4_uartGetRegisters(handle->device);
    STM32F4_UARTIRQSource_t irq_source;

    if (uart->SR & USART_SR_IDLE)
        irq_source = UART_IRQ_LINE_IDLE;
    else if (uart->SR & USART_SR_RXNE || USART1->SR & USART_SR_ORE)
        irq_source = UART_IRQ_RXNE_OVERRUN;
    else if (uart->SR & USART_SR_TC)
        irq_source = UART_IRQ_TX_COMPLETE;
    else if (uart->SR & USART_SR_TXE)
        irq_source = UART_IRQ_TX_EMPTY;
    else if (uart->SR & USART_SR_PE)
        irq_source = UART_IRQ_PARTITY_ERROR;
    else if (uart->SR & USART_SR_LBD)
        irq_source = UART_IRQ_LINE_BREAK;
    else if (uart->SR & USART_SR_NE || USART1->SR & USART_SR_FE)
        irq_source = UART_IRQ_NOISE_FRAMING;
    else if (handle->device != STM32F4_UART_4 && handle->device != STM32F4_UART_4 && uart->SR & USART_SR_CTS)
        irq_source = UART_IRQ_CTS_CHANGE;

    int idx = stm32f4_uartIRQToIndex(irq_source);
    for (int i = 0; i < STM32F4_MAX_CALLBACK_COUNT; ++i) {
        if (callback_set[idx][i])
            callback_set[idx][i]();
    }

    stm32f4_uartClearIRQPending(handle, irq_source);
}

//=============================================================================================
// UART INTERRUPT HANDLERS
//=============================================================================================

void USART1_IRQHandler()
{
    UARTHandle_t handle;
    handle.device = STM32F4_USART_1;
    stm32f4_uartHandleInterrupt(&handle, usart1_callbacks);
}

void USART2_IRQHandler()
{
    UARTHandle_t handle;
    handle.device = STM32F4_USART_2;
    stm32f4_uartHandleInterrupt(&handle, usart2_callbacks);
}

void USART3_IRQHandler()
{
    UARTHandle_t handle;
    handle.device = STM32F4_USART_3;
    stm32f4_uartHandleInterrupt(&handle, usart3_callbacks);
}

void UART4_IRQHandler()
{
    UARTHandle_t handle;
    handle.device = STM32F4_UART_4;
    stm32f4_uartHandleInterrupt(&handle, uart4_callbacks);
}

void UART5_IRQHandler()
{
    UARTHandle_t handle;
    handle.device = STM32F4_UART_5;
    stm32f4_uartHandleInterrupt(&handle, uart5_callbacks);
}

void USART6_IRQHandler()
{
    UARTHandle_t handle;
    handle.device = STM32F4_USART_6;
    stm32f4_uartHandleInterrupt(&handle, usart6_callbacks);
}

//=============================================================================================
// INTERFACE FUNCTIONS
//=============================================================================================

uint8_t stm32f4_uartToIRQChannel(UARTHandle_t *handle)
{
    switch (handle->device) {
    case STM32F4_USART_1:   return USART1_IRQn;
    case STM32F4_USART_2:   return USART2_IRQn;
    case STM32F4_USART_3:   return USART3_IRQn;
    case STM32F4_UART_4:    return UART4_IRQn;
    case STM32F4_UART_5:    return UART5_IRQn;
    case STM32F4_USART_6:   return USART6_IRQn;
    }

    return 0;
}

bool stm32f4_uartRegisterCallback(UARTHandle_t *handle, STM32F4_UARTIRQSource_t irq_source, HALEventCallback_t callback)
{
    HALEventCallback_t *callback_set = NULL;
    int idx = stm32f4_uartIRQToIndex(irq_source);

    switch (handle->device) {
    case STM32F4_USART_1:   callback_set = usart1_callbacks[idx]; break;
    case STM32F4_USART_2:   callback_set = usart2_callbacks[idx]; break;
    case STM32F4_USART_3:   callback_set = usart3_callbacks[idx]; break;
    case STM32F4_UART_4:    callback_set = uart4_callbacks[idx]; break;
    case STM32F4_UART_5:    callback_set = uart5_callbacks[idx]; break;
    case STM32F4_USART_6:   callback_set = usart6_callbacks[idx]; break;
    default:                return false;
    }

    bool status = stm32f4_addCallback(callback_set, callback);
    stm32f4_uartEnableIRQ(handle, irq_source, true);

    return status;
}

bool stm32f4_uartUnregisterCallback(UARTHandle_t *handle, STM32F4_UARTIRQSource_t irq_source, HALEventCallback_t callback)
{
    HALEventCallback_t *callback_set = NULL;
    int idx = stm32f4_uartIRQToIndex(irq_source);

    switch (handle->device) {
    case STM32F4_USART_1:   callback_set = usart1_callbacks[idx]; break;
    case STM32F4_USART_2:   callback_set = usart2_callbacks[idx]; break;
    case STM32F4_USART_3:   callback_set = usart3_callbacks[idx]; break;
    case STM32F4_UART_4:    callback_set = uart4_callbacks[idx]; break;
    case STM32F4_UART_5:    callback_set = uart5_callbacks[idx]; break;
    case STM32F4_USART_6:   callback_set = usart6_callbacks[idx]; break;
    default:                return false;
    }

    int used_slots = STM32F4_MAX_CALLBACK_COUNT;
    bool status = stm32f4_removeCallback(callback_set, callback, &used_slots);
    if (used_slots == 0)
        stm32f4_uartEnableIRQ(handle, irq_source, false);

    return status;
}
