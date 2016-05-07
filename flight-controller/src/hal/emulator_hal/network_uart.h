////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       15.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef NETWORK_UART_H
#define NETWORK_UART_H

#include "hal/uart.h"

#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>

#define IP_MAX_SIZE     16

typedef struct {
    uint8_t ip[IP_MAX_SIZE];
    uint16_t port;
} Emulator_UARTConfig_t;

typedef struct {
    bool connected;
    bool enabled;
    struct sockaddr_in server_addr;
} NetworkUARTPrivateData_t;

bool emulator_uartInit(UARTHandle_t *handle, Emulator_UARTConfig_t *config);

#endif
