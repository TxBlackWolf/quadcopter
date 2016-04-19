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
#include "common/commands/commands.h"
#include "common/commands/emulator.h"

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
    EmulatorGPIOPrivateData_t *private_data = (EmulatorGPIOPrivateData_t *) malloc(sizeof(LinuxTimerPrivateData_t));
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
    private_data->enabled = true;
}

void gpio_deactivate(GPIOHandle_t *handle)
{
    EmulatorGPIOPrivateData_t *private_data = (EmulatorGPIOPrivateData_t *) handle->private_data;
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
    /// @todo Implement most of this as a part of commands framework.

    int commandSize = sizeof(CommandHeader_t) + sizeof(EmulatorCommand_t) + sizeof(EmulatorCommandGPIO_t);
    uint8_t *buffer = (uint8_t *) malloc(commandSize);
    if(buffer == NULL)
        return false;

    int idx = 0;
    CommandHeader_t *header = &buffer[idx];
    header->version_major = 0;
    header->version_minor = 0;
    header->version_patch = 1;
    header->command_id = 0;
    header->type = COMMAND_EMULATOR;
    header->payload_size = 15;
    header->payload_crc = 0;
    idx += sizeof(CommandHeader_t);

    EmulatorCommand_t *emulatorCommand = &buffer[idx];
    emulatorCommand->device = EMULATED_DEVICE_GPIO;
    idx += sizeof(EmulatorCommand_t);

    EmulatorCommandGPIO_t *gpioCommand = &buffer[idx];
    gpioCommand->port = handle->port;
    gpioCommand->pin = handle->pin;
    gpioCommand->value = 1;
    gpioCommand->name_size = 0;



    free(buffer);
}

bool gpio_writePort(GPIOHandle_t *handle, uint16_t value)
{

}

void gpio_pinConfigLock(GPIOHandle_t *handle __attribute__((unused)))
{
    // Empty.
}
