////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       18.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "command_control.h"

#include <stdio.h>

static CommandCallback_t command_callbacks[CONTROL_EVENT_COUNT];

bool command_registerControlCallback(ControlEvent_t event, CommandCallback_t callback)
{
    if(command_callbacks[event])
        return false;

    command_callbacks[event] = callback;
    return true;
}

bool command_unregisterControlCallback(ControlEvent_t event)
{
    if(!command_callbacks[event])
        return false;

    command_callbacks[event] = NULL;
    return true;
}

CommandDecoderError_t command_parseControl(uint8_t *payload, uint32_t size)
{
    ControlHeader_t *header = (ControlHeader_t *) payload;
    if(!command_callbacks[header->event])
        return PARSING_INVALID_DATA;

    uint8_t *command = payload + sizeof(ControlHeader_t);
    uint32_t command_size = size - sizeof(ControlHeader_t);
    command_callbacks[header->event](command, command_size);

    return PARSING_OK;
}
