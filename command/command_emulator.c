////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       18.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "command_emulator.h"

#include <stdio.h>

static CommandCallback_t command_callbacks[EMULATED_DEVICE_COUNT];

bool command_registerEmulatorCallback(EmulatedDevice_t device, CommandCallback_t callback)
{
    if (command_callbacks[device])
        return false;

    command_callbacks[device] = callback;
    return true;
}

bool command_unregisterEmulatorCallback(EmulatedDevice_t device)
{
    if (!command_callbacks[device])
        return false;

    command_callbacks[device] = NULL;
    return true;
}

CommandDecoderError_t command_parseEmulator(uint8_t *payload, uint32_t size)
{
    EmulatorHeader_t *header = (EmulatorHeader_t *) payload;
    if (!command_callbacks[header->device])
        return PARSING_INVALID_DATA;

    uint8_t *command = payload + sizeof(EmulatorHeader_t);
    uint32_t command_size = size - sizeof(EmulatorHeader_t);
    command_callbacks[header->device](command, command_size);

    return PARSING_OK;
}
