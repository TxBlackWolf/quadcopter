//=============================================================================================
//
// Filename   : network_uart.h
// Author     : Kuba Sejdak
// Created on : 15.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef NETWORK_UART_H
#define NETWORK_UART_H

#include "hal/uart.h"

#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>

#define IP_MAX_SIZE     16

typedef enum {
    UART_CONNECTION_TCP,
    UART_CONNECTION_UDP
} Emulator_UARTConnectionProtocol_t;

typedef struct {
    uint8_t ip[IP_MAX_SIZE];
    uint16_t port;
    Emulator_UARTConnectionProtocol_t protocol;
} Emulator_UARTConfig_t;

typedef struct {
    bool connected;
    bool enabled;
    struct sockaddr_in server_addr;
} NetworkUARTPrivateData_t;

bool emulator_uartInit(UARTHandle_t *handle, Emulator_UARTConfig_t *config);

#endif
