////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       09.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "emulator_gpio.h"
#include "board/console.h"
#include "command/command_emulator.h"
#include "command/command_encoder.h"
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
    EmulatorCommandGPIO_t gpio_command;
    gpio_command.port = handle->port;
    gpio_command.pin = handle->pin;
    gpio_command.value = value;
    strncpy((char *) gpio_command.name, handle->name, PIN_NAME_MAX_SIZE);
    gpio_command.name[PIN_NAME_MAX_SIZE - 1] = '\0';

    uint8_t command[COMMAND_MAX_SIZE_BYTES];
    int command_size = commandEncoder_createEmulatorCommand(command, EMULATED_DEVICE_GPIO, &gpio_command);

    return commandsManager_send(command, command_size);
}

bool gpio_writePort(GPIOHandle_t *handle, uint16_t value)
{
    return false;
}

void gpio_pinConfigLock(GPIOHandle_t *handle __attribute__((unused)))
{
    // Empty.
}
