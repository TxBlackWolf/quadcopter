//---------------------------------------------------------------------------------------------------------------
//
// Filename   : UART.h
// Author     : Kuba Sejdak
// Created on : 11.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef UART_H
#define UART_H

#include <stdbool.h>

// Number and type of UART device.
typedef enum
{
    // UART
    UART_1,
    UART_2,
    UART_3,
    UART_4,
    UART_5,

    // USART
    USART_1,
    USART_2,
    USART_3,
    USART_4,
    USART_5,
    USART_6
} UARTDevice_t;

typedef enum
{
    UART_TX,
    UART_RX,
    UART_BIDIRECTIONAL
} UARTDirection_t;

bool UARTInit(UARTDevice_t device, UARTDirection_t direction);

#endif
