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

static bool stm32f4_uartCheckIRQSource(UARTDevice_t device, uint16_t flag)
{
    STM32F4_UARTPrivateData_t *private_data = &uarts_privateData[device - 1];
    if ((private_data->irq_flags & flag) == 0)
        return false;

    UART_t *uart = stm32f4_uartGetRegisters(device);
    return (uart->SR & flag);
}

static void stm32f4_uartHandleInterrupt(UARTDevice_t device, HALEventCallback_t callback_set[][STM32F4_MAX_CALLBACK_COUNT])
{
    STM32F4_UARTIRQSource_t irq_source;

    if (stm32f4_uartCheckIRQSource(device, USART_SR_IDLE))
        irq_source = UART_IRQ_LINE_IDLE;
    else if (stm32f4_uartCheckIRQSource(device, USART_SR_RXNE | USART_SR_ORE))
        irq_source = UART_IRQ_RXNE_OVERRUN;
    else if (stm32f4_uartCheckIRQSource(device, USART_SR_TC))
        irq_source = UART_IRQ_TX_COMPLETE;
    else if (stm32f4_uartCheckIRQSource(device, USART_SR_TXE))
        irq_source = UART_IRQ_TX_EMPTY;
    else if (stm32f4_uartCheckIRQSource(device, USART_SR_PE))
        irq_source = UART_IRQ_PARTITY_ERROR;
    else if (stm32f4_uartCheckIRQSource(device, USART_SR_LBD))
        irq_source = UART_IRQ_LINE_BREAK;
    else if (stm32f4_uartCheckIRQSource(device, USART_SR_NE | USART_SR_FE))
        irq_source = UART_IRQ_NOISE_FRAMING;
    else if (device != STM32F4_UART_4 && device != STM32F4_UART_5 && stm32f4_uartCheckIRQSource(device, USART_SR_CTS))
        irq_source = UART_IRQ_CTS_CHANGE;

    int idx = stm32f4_uartIRQToIndex(irq_source);
    for (int i = 0; i < STM32F4_MAX_CALLBACK_COUNT; ++i) {
        if (callback_set[idx][i])
            callback_set[idx][i]();
    }

    UARTHandle_t handle;
    handle.device = device;
    stm32f4_uartClearIRQPending(&handle, irq_source);
}

//=============================================================================================
// UART INTERRUPT HANDLERS
//=============================================================================================

void USART1_IRQHandler()
{
    stm32f4_uartHandleInterrupt(STM32F4_USART_1, usart1_callbacks);
}

void USART2_IRQHandler()
{
    stm32f4_uartHandleInterrupt(STM32F4_USART_2, usart2_callbacks);
}

void USART3_IRQHandler()
{
    stm32f4_uartHandleInterrupt(STM32F4_USART_3, usart3_callbacks);
}

void UART4_IRQHandler()
{
    stm32f4_uartHandleInterrupt(STM32F4_UART_4, uart4_callbacks);
}

void UART5_IRQHandler()
{
    stm32f4_uartHandleInterrupt(STM32F4_UART_5, uart5_callbacks);
}

void USART6_IRQHandler()
{
    stm32f4_uartHandleInterrupt(STM32F4_USART_6, usart6_callbacks);
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

uint16_t stm32f4_uartIRQToStatusFlag(STM32F4_UARTIRQSource_t irq_source)
{
    switch (irq_source) {
    case UART_IRQ_LINE_IDLE:        return USART_SR_IDLE;
    case UART_IRQ_RXNE_OVERRUN:     return (USART_SR_RXNE | USART_SR_ORE);
    case UART_IRQ_TX_COMPLETE:      return USART_SR_TC;
    case UART_IRQ_TX_EMPTY:         return USART_SR_TXE;
    case UART_IRQ_PARTITY_ERROR:    return USART_SR_PE;
    case UART_IRQ_LINE_BREAK:       return USART_SR_LBD;
    case UART_IRQ_NOISE_FRAMING:    return (USART_SR_NE | USART_SR_FE);
    case UART_IRQ_CTS_CHANGE:       return USART_SR_CTS;
    default:                        break;
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
