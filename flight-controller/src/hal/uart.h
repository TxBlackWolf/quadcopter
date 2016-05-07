////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.08.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef UART_H
#define UART_H

#include "gpio.h"

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t UARTDevice_t;
typedef uint32_t UARTBaurRate_t;

// UART data bits.
typedef enum {
    UART_DATA_BITS_7,
    UART_DATA_BITS_8,
    UART_DATA_BITS_9
} UARTDataBits_t;

// UART stop bits.
typedef enum {
    UART_STOP_BITS_0_5 ,
    UART_STOP_BITS_1,
    UART_STOP_BITS_1_5,
    UART_STOP_BITS_2
} UARTStopBits_t;

// UART partity.
typedef enum {
    UART_PARTITY_NONE,
    UART_PARTITY_EVEN,
    UART_PARTITY_ODD
} UARTPartity_t;

// UART flow control.
typedef enum {
    UART_FLOW_CONTROL_NONE,
    UART_FLOW_CONTROL_RTS_CTS,
    UART_FLOW_CONTROL_XON_XOFF
} UARTFlowControl_t;

// Protocol configuration structure.
typedef struct {
    UARTBaurRate_t baud_rate;
    UARTDataBits_t data_bits;
    UARTStopBits_t stop_bits;
    UARTPartity_t parity;
    UARTFlowControl_t flow_control;
} UARTProtocolConfig_t;

// UART direction.
typedef enum {
    UART_DIRECTION_READ,
    UART_DIRECTION_WRITE,
    UART_DIRECTION_BIDIRECTIONAL
} UARTDirection_t;

// UART mode.
typedef enum {
    UART_MODE_SYNCHRONOUS,
    UART_MODE_ASYNCHRONOUS
} UARTMode_t;

// UART configuration structure.
typedef struct {
    UARTProtocolConfig_t protocol;
    UARTDirection_t direction;
    UARTMode_t mode;
} UARTConfig_t;

// UART handle.
typedef struct {
    UARTDevice_t device;
    GPIOHandle_t uart_gpio;
    void *private_data;
} UARTHandle_t;

void uart_activate(UARTHandle_t *handle);
void uart_deactivate(UARTHandle_t *handle);

bool uart_send(UARTHandle_t *handle, uint16_t data);
bool uart_receive(UARTHandle_t *handle, uint16_t *data);

#endif
