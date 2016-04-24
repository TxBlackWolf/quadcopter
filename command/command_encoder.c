////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       24.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
//////////////////////////////////////////////////////////////////////////////////////////////// 

#include "command_encoder.h"
#include "command_common.h"

static uint32_t commandEncoder_nextId = 0;

/// @brief Initialized common command header in given buffer.
/// @param [in/out] buffer          Buffer for command.
/// @return Size of created data.
static int commandEncoder_initHeader(uint8_t *buffer)
{
    /// @todo Add automatic version deserialization from string.
    CommandHeader_t *header = (CommandHeader_t *) buffer;
    header->sync1 = COMMANDS_SYNC_WORD_1;
    header->sync2 = COMMANDS_SYNC_WORD_2;
    header->sync3 = COMMANDS_SYNC_WORD_3;
    header->version_major = 0;
    header->version_minor = 0;
    header->version_patch = 1;
    header->command_id = commandEncoder_nextId++;
    header->type = type;
    header->payload_size = 0;
    header->payload_crc = 0;

    return sizeof(CommandHeader_t);
}

int commandEncoder_createEmulatorCommand(uint8_t *buffer, EmulatedDevice_t device, void *command)
{
    int idx = commandEncoder_initHeader(buffer);
    
    EmulatorHeader_t *emulatorHeader = &buffer[idx];
    emulatorHeader->device = device;
    
    idx += sizeof(EmulatorHeader_t);
    
    return idx;
}

void commandEncoder_finish(uint8_t *buffer, int size)
{
    CommandHeader_t *header = (CommandHeader_t *) buffer;
    header->payload_size = size - sizeof(CommandHeader_t);
    header->payload_crc = 0;

    if(crc_functor)
        header->payload_crc = crc_functor(buffer + sizeof(CommandHeader_t), header->payload_size);
}