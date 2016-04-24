//=============================================================================================
//
// Filename   : network_uart.c
// Author     : Kuba Sejdak
// Created on : 15.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#include "network_uart.h"
#include "board/console.h"

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

//=============================================================================================
// INTERFACE FUNCTIONS
//=============================================================================================

bool emulator_uartInit(UARTHandle_t *handle, Emulator_UARTConfig_t *config)
{
    // Allocate and init private data.
    NetworkUARTPrivateData_t *private_data = (NetworkUARTPrivateData_t *) malloc(sizeof(NetworkUARTPrivateData_t));
    if(!private_data) {
        console_write("network_uart: Failed to alloc network UART private data: %s", strerror(errno));
        return false;
    }

    private_data->enabled = false;

    // Create socket.
    int sock = socket(AF_INET, (config->protocol == UART_CONNECTION_TCP) ? SOCK_STREAM : SOCK_DGRAM, 0);
    if(sock == -1) {
        console_write("network_uart: Failed to create socket for UART: %s.", strerror(errno));
        return false;
    }

    // Prepare server address.
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(config->port);
    if(inet_pton(AF_INET, (char *) config->ip, &server_addr.sin_addr) != 1) {
        console_write("network_uart: Failed to convert IP string to binary form: %s.", strerror(errno));
        return false;
    }

    if(config->protocol == UART_CONNECTION_TCP) {
        // Connect to server.
        if(connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
            console_write("network_uart: Failed to connect to server [%s:%d]: %s\n", config->ip, config->port, strerror(errno));
            return false;
        }
    }

    memcpy(&private_data->server_addr, &server_addr, sizeof(server_addr));

    handle->device = sock;
    handle->private_data = private_data;
    return true;
}

void uart_activate(UARTHandle_t *handle)
{
    NetworkUARTPrivateData_t *private_data = (NetworkUARTPrivateData_t *) handle->private_data;
    assert(private_data);
    private_data->enabled = true;
}

void uart_deactivate(UARTHandle_t *handle)
{
    NetworkUARTPrivateData_t *private_data = (NetworkUARTPrivateData_t *) handle->private_data;
    assert(private_data);
    private_data->enabled = false;
}

bool uart_send(UARTHandle_t *handle, uint16_t data)
{
    NetworkUARTPrivateData_t *private_data = (NetworkUARTPrivateData_t *) handle->private_data;
    assert(private_data);
    if(!private_data->enabled)
        return false;

    if(sendto(handle->device, &data, sizeof(uint8_t), 0, (struct sockaddr *) &private_data->server_addr, sizeof(private_data->server_addr)) == -1)
        return false;

    return true;
}

bool uart_receive(UARTHandle_t *handle, uint16_t *data)
{
    NetworkUARTPrivateData_t *private_data = (NetworkUARTPrivateData_t *) handle->private_data;
    assert(private_data);
    if(!private_data->enabled)
        return false;

    socklen_t sock_len = sizeof(private_data->server_addr);
    if(recvfrom(handle->device, data, sizeof(uint8_t), 0, (struct sockaddr *) &private_data->server_addr, &sock_len) == -1)
        return false;

    return true;
}
