////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       18.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "emulator.h"

#include <stdio.h>

static CommandCallback_t command_callbacks[EMULATED_DEVICE_COUNT];

bool command_registerEmulatorCallback(EmulatedDevice_t device, CommandCallback_t callback)
{
    if(command_callbacks[device])
        return false;

    command_callbacks[device] = callback;
    return true;
}

bool command_unregisterEmulatorCallback(EmulatedDevice_t device)
{
    if(!command_callbacks[device])
        return false;

    command_callbacks[device] = NULL;
    return true;
}

bool command_parseEmulator(uint8_t *payload, uint32_t size)
{
    EmulatorCommand_t *command = (EmulatorCommand_t *) payload;
    if(!command_callbacks[command->device])
        return false;

    command_callbacks[command->device](payload, size);
    return true;
}
