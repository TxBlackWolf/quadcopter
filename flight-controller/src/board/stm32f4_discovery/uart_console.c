//---------------------------------------------------------------------------------------------------------------
//
// Filename   : uart_console.c
// Author     : Kuba Sejdak
// Created on : 22.07.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "board/console.h"
#include "uart_console.h"
#include "hal/uart.h"

bool console_init()
{
    return uart_init(USART_1, UART_TX);
}

int console_write(const char *format, ...)
{
    // TODO: implement.
    return 0;
}

