//=============================================================================================
//
// Filename   : network_uart.c
// Author     : Kuba Sejdak
// Created on : 09.04.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#include "emulator_gpio.h"
#include "board/console.h"
#include "common/commands/commands.h"
#include "common/commands/emulator.h"
#include "core/controller/commands_manager.h"

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>

//=============================================================================================
// INTERFACE FUNCTIONS
//=============================================================================================

bool emulator_gpioInit(GPIOHandle_t *handle)
{
    // Allocate and init private data.
    EmulatorGPIOPrivateData_t *private_data = (EmulatorGPIOPrivateData_t *) malloc(sizeof(EmulatorGPIOPrivateData_t));
    if(!private_data) {
        console_write("emulator_gpio: Failed to alloc emulator GPIO private data: %s.\n", strerror(errno));
        return false;
    }

    private_data->enabled = false;

    handle->private_data = private_data;
    return true;
}

void gpio_activate(GPIOHandle_t *handle)
{
    EmulatorGPIOPrivateData_t *private_data = (EmulatorGPIOPrivateData_t *) handle->private_data;
    assert(private_data);
    private_data->enabled = true;
}

void gpio_deactivate(GPIOHandle_t *handle)
{
    EmulatorGPIOPrivateData_t *private_data = (EmulatorGPIOPrivateData_t *) handle->private_data;
    assert(private_data);
    private_data->enabled = false;
}

bool gpio_readPin(GPIOHandle_t *handle)
{
    /// @todo Implement.
    return false;
}

uint16_t gpio_readPort(GPIOHandle_t *handle)
{
    /// @todo Implement.
    return 0;
}

bool gpio_writePin(GPIOHandle_t *handle, bool value)
{
    uint8_t command[COMMANDS_MAX_SIZE_BYTES];
    memset(command, 0, COMMANDS_MAX_SIZE_BYTES);
    int command_size = 0;
    EmulatorCommandGPIO_t *gpio_command = command_create(command, &command_size, COMMAND_EMULATOR, EMULATED_DEVICE_GPIO);

    gpio_command->port = handle->port;
    gpio_command->pin = handle->pin;
    gpio_command->value = value;
    gpio_command->name_size = strlen(handle->name) + 1;
    command_size += sizeof(EmulatorCommandGPIO_t);
    strcpy((char *) command + command_size, handle->name);
    command_size += gpio_command->name_size;

    command_finish(command, command_size);
    return commandsManager_send(command);
}

bool gpio_writePort(GPIOHandle_t *handle, uint16_t value)
{
    return false;
}

void gpio_pinConfigLock(GPIOHandle_t *handle __attribute__((unused)))
{
    // Empty.
}
