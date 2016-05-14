////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       15.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "network_uart.h"
#include "board/console.h"

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

//=============================================================================================
// HELPER FUNCTIONS
//=============================================================================================

static char *emulator_addressToString(struct sockaddr_in *addr)
{
    static char ip_string[64];
    inet_ntop(addr->sin_family, &addr->sin_addr, ip_string, sizeof(ip_string));
    sprintf(ip_string, "%s:%d", ip_string, ntohs(addr->sin_port));

    return ip_string;
}

static bool emulator_connect(UARTHandle_t *handle)
{
    // Create socket.
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        return false;

    handle->device = sock;

    NetworkUARTPrivateData_t *private_data = (NetworkUARTPrivateData_t *) handle->private_data;
    //static bool first = true;

    if(connect(handle->device, (struct sockaddr *) &private_data->server_addr, sizeof(private_data->server_addr)) != 0) {
        private_data->connected = false;
        close(sock);
    }
    else {
        private_data->connected = true;
        console_write("network_uart: Connected to server [%s]\n", emulator_addressToString(&private_data->server_addr));
    }

    return private_data->connected;
}

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

    private_data->connected = false;
    private_data->enabled = false;

    // Prepare server address.
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(config->port);
    if(inet_pton(AF_INET, (char *) config->ip, &server_addr.sin_addr) != 1) {
        console_write("network_uart: Failed to convert IP string to binary form: %s", strerror(errno));
        free(private_data);
        return false;
    }

    handle->private_data = private_data;
    memcpy(&private_data->server_addr, &server_addr, sizeof(server_addr));

    return emulator_connect(handle);
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
    if(!private_data->connected) {
        if(!emulator_connect(handle))
            return false;
    }

    if(!private_data->enabled)
        return false;

    if(sendto(handle->device, &data, sizeof(uint8_t), MSG_NOSIGNAL, (struct sockaddr *) &private_data->server_addr, sizeof(private_data->server_addr)) == -1) {
        if(errno == EPIPE) {
            private_data->connected = false;
            close(handle->device);
        }

        return false;
    }

    return true;
}

bool uart_receive(UARTHandle_t *handle, uint16_t *data)
{
    NetworkUARTPrivateData_t *private_data = (NetworkUARTPrivateData_t *) handle->private_data;
    assert(private_data);
    if(!private_data->connected) {
        if(!emulator_connect(handle))
            return false;
    }

    if(!private_data->enabled)
        return false;

    socklen_t sock_len = sizeof(private_data->server_addr);
    if(recvfrom(handle->device, data, sizeof(uint8_t), 0, (struct sockaddr *) &private_data->server_addr, &sock_len) == -1)
        return false;

    return true;
}
