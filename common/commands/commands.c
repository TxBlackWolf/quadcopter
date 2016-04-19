////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       15.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "commands.h"
#include "emulator.h"

#include <stdio.h>

static uint32_t command_nextId = 0;
static uint32_t command_receivedCount = 0;
static uint32_t command_lostCount = 0;
static uint32_t command_brokenCount = 0;

static CRCFunctor crc_functor = NULL;

bool command_checkVersion(CommandHeader_t *header)
{
    /// @todo Implement.
    return true;
}

bool command_checkId(CommandHeader_t *header)
{
    uint32_t expectedId = command_nextId;
    command_nextId = header->command_id + 1;

    return (header->command_id == expectedId);
}

bool command_checkCRC(uint8_t *buffer, uint32_t size, uint32_t crc)
{
    /// @todo Implement.
    return true;
}

void *command_create(uint8_t *buffer, int *size, CommandType_t type, int subtype)
{
    int idx = 0;

    /// @todo Add automatic version deserialization from string.
    CommandHeader_t *header = (CommandHeader_t *) &buffer[idx];
    header->version_major = 0;
    header->version_minor = 0;
    header->version_patch = 1;
    header->command_id = command_nextId++;
    header->type = type;
    header->payload_size = 0;
    header->payload_crc = 0;
    idx += sizeof(CommandHeader_t);

    switch(type) {
    case COMMAND_EMULATOR: {
            EmulatorCommand_t *emulatorCommand = (EmulatorCommand_t *) &buffer[idx];
            emulatorCommand->device = subtype;
            idx += sizeof(EmulatorCommand_t);
        }
        break;
    default:
        break;
    }

    *size = idx;
    return buffer + idx;
}

void command_finish(uint8_t *buffer, int size)
{
    CommandHeader_t *header = (CommandHeader_t *) buffer;
    header->payload_size = size - sizeof(CommandHeader_t);
    header->payload_crc = 0;

    if(crc_functor)
        header->payload_crc = crc_functor(buffer + sizeof(CommandHeader_t), header->payload_size);
}

CommandParsingError_t command_parse(uint8_t *buffer)
{
    CommandHeader_t *header = (CommandHeader_t *) buffer;
    ++command_receivedCount;

    if(!command_checkVersion(header)) {
        ++command_brokenCount;
        return PARSING_BAD_VERSION;
    }

    if(!command_checkId(header))
        ++command_lostCount;

    if(!command_checkCRC(buffer + sizeof(CommandHeader_t), header->payload_size, header->payload_crc)) {
        ++command_brokenCount;
        return PARSING_BAD_CRC;
    }

    bool parsing_stat = false;
    switch(header->type) {
    case COMMAND_EMULATOR:
        parsing_stat = command_parseEmulator(buffer + sizeof(CommandHeader_t), header->payload_size);
        break;
    case COMMAND_CONTROL:
        ++command_brokenCount;
        return PARSING_UNSUPPORTED_TYPE;
    case COMMAND_TELEMETRY:
        ++command_brokenCount;
        return PARSING_UNSUPPORTED_TYPE;
    case COMMAND_SYS_STATUS:
        ++command_brokenCount;
        return PARSING_UNSUPPORTED_TYPE;
    case COMMAND_DEBUG:
        ++command_brokenCount;
        return PARSING_UNSUPPORTED_TYPE;
    default:
        ++command_brokenCount;
        return PARSING_UNSUPPORTED_TYPE;
    }

    if(!parsing_stat) {
        ++command_brokenCount;
        return PARSING_INVALID_DATA;
    }

    return PARSING_OK;
}
