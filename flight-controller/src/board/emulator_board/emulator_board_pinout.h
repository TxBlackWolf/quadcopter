//=============================================================================================
//
// Filename   : emulator_board_pinout.c
// Author     : Kuba Sejdak
// Created on : 04.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef EMULATOR_BOARD_PINOUT_H
#define EMULATOR_BOARD_PINOUT_H

#include "hal/emulator_hal/network_uart.h"

// Network console.
#define NETWORK_CONSOLE_IP                      "127.0.0.1"
#define NETWORK_CONSOLE_PORT                    12555
#define NETWORK_CONSOLE_PROTOCOL                UART_CONNECTION_TCP

// Network commands.
#define NETWORK_COMMANDS_IP                     "127.0.0.1"
#define NETWORK_COMMANDS_PORT                   12556
#define NETWORK_COMMANDS_PROTOCOL               UART_CONNECTION_TCP

#endif
