////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       23.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "command_decoder.h"
#include "command_emulator.h"

#include <stdio.h>

bool commandDecoder_checkVersion(CommandHeader_t *header)
{
    /// @todo Implement.
    return true;
}

bool commandDecoder_checkId(CommandHeader_t *header)
{
    uint32_t expectedId = command_nextId;
    command_nextId = header->command_id + 1;

    return (header->command_id == expectedId);
}

CommandParsingStatus_t commandDecoder_parse(const uint8_t *buffer)
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
