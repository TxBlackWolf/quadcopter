//---------------------------------------------------------------------------------------------------------------
//
// Filename   : UARTConsole.c
// Author     : Kuba Sejdak
// Created on : 22.07.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "Platform/Console.h"
#include "UARTConsole.h"
#include "Drivers/UART.h"

bool console_init()
{
    return UARTInit(USART_1, UART_TX);
}

int console_write(const char *format, ...)
{
    // TODO: implement.
    return 0;
}

