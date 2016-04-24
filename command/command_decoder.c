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

static uint8_t *internal_buffer = NULL;
static bool commandDecoder_nextIdFound = false;
static uint32_t commandDecoder_nextId = 0;
static CommandDecoderState_t decoder_state = DECODER_NO_COMMAND;

/// @brief Checks, if this message is compatible with this framework.
/// @param [in] header              Command header.
/// @return True if command is compatible, false otherwise.
static bool commandDecoder_checkVersion(CommandHeader_t *header)
{
    /// @todo Implement.
    return true;
}

/// @brief Checks, if this message is next in sequence order,
/// @param [in] header              Command header.
/// @return True if command has expected sequence id, false otherwise.
static bool commandDecoder_checkId(CommandHeader_t *header)
{
    if(!commandDecoder_nextIdFound) {
        commandDecoder_nextId = header->command_id + 1;
        commandDecoder_nextIdFound = true;
        return true; 
    }

    return (header->command_id == commandDecoder_nextId++);
}

void commandDecoder_init(uint8_t *buffer)
{
    internal_buffer = buffer;
}

CommandDecoderState_t commandDecoder_feed(const uint8_t *buffer, int size)
{
    command_copyBuffer(internal_buffer, buffer, size);
    
    switch(decoder_state) {
    case DECODER_NO_COMMAND:
        break;
    case DECODER_SYNC1:
        break;
    case DECODER_SYNC2:
        break;
    case DECODER_SYNC3:
        break;
    case DECODER_COMMAND_INCOMPLETE:
        break;
    case DECODER_COMMAND_COMPLETE:
        break;
    }
}

CommandDecoderError_t commandDecoder_parse()
{
    decoder_state = DECODER_NO_COMMAND;
    return PARSING_OK;
}

/*
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
*/
