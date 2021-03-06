////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       04.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "printf_console.h"
#include "emulator_board_pinout.h"
#include "hal/emulator_hal/network_uart.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define CONSOLE_BUFFER_SIZE     1024

static UARTHandle_t uart_handle;
static bool console_initialized = false;

bool console_init()
{
    // Try to init network console first.
    Emulator_UARTConfig_t uart_config;
    strcpy((char *) uart_config.ip, NETWORK_CONSOLE_IP);
    uart_config.port = NETWORK_CONSOLE_PORT;

    emulator_uartInit(&uart_handle, &uart_config);
    uart_activate(&uart_handle);
    console_initialized = true;

    console_write("\n");
    return console_initialized;
}

void console_write(const char *format, ...)
{
    if(!console_initialized)
        return;

    char buffer[CONSOLE_BUFFER_SIZE];

    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    for(int i = 0; buffer[i]; ++i) {
        if(!uart_send(&uart_handle, buffer[i])) {
            printf("%s", buffer);
            fflush(stdout);
            break;
        }
    }
}
