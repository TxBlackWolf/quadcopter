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
#include "command_common.h"
#include "command_emulator.h"

#include <stdio.h>

#define MIN(x,y)        (((x) < (y)) ? (x) : (y))

typedef struct {
    uint8_t *buffer;
    int offset;
    uint32_t data_size;
    uint32_t expected_size;
    bool id_initialized;
    uint32_t expected_id;
    CommandDecoderState_t state;
} CommandDecoder_t;

static CommandDecoder_t decoder;

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
    if(!decoder.id_initialized) {
        decoder.expected_id = header->command_id + 1;
        decoder.id_initialized = true;
        return true; 
    }

    return (header->command_id == decoder.expected_id++);
}

/// @brief Looks for synchronization byte in internal buffer.
/// @return One position after synchronization word.
static int commandDecoder_findSync(int offset, uint8_t sync_byte)
{
    uint8_t *buffer = decoder.buffer + offset; 
    for(unsigned int i = 0; i < decoder.data_size; ++i) {
        if(buffer[i] == sync_byte)
            return i + 1;
    }

    return -1;
}

void commandDecoder_init(uint8_t *buffer)
{
    decoder.buffer = buffer;
    decoder.offset = 0;
    decoder.data_size = 0;
    decoder.expected_size = 0;
    decoder.id_initialized = false;
    decoder.expected_id = 0;
    decoder.state = DECODER_NO_COMMAND;
}

CommandDecoderState_t commandDecoder_feed(const uint8_t *buffer, int size)
{
    command_copyBuffer(decoder.buffer + decoder.data_size, buffer, size);
    decoder.data_size += size;

    int start = 0;
    bool done = false;

    while(!done) {
        switch(decoder.state) {
        case DECODER_NO_COMMAND:
            decoder.offset = commandDecoder_findSync(decoder.offset, COMMAND_SYNC_BYTE_1);
            if(decoder.offset < 0) {
                decoder.data_size = 0;
                decoder.offset = 0;
                done = true;
            }
            
            start = decoder.offset;
            decoder.state = DECODER_SYNC1;
            break;

        case DECODER_SYNC1:
            decoder.offset = commandDecoder_findSync(decoder.offset, COMMAND_SYNC_BYTE_2);
            if(decoder.offset < 0) {
                decoder.state = DECODER_NO_COMMAND;
                decoder.offset = start;
            }
            else
                decoder.state = DECODER_SYNC2;
            break;

        case DECODER_SYNC2:
            decoder.offset = commandDecoder_findSync(decoder.offset, COMMAND_SYNC_BYTE_3);
            if(decoder.offset < 0) {
                decoder.state = DECODER_NO_COMMAND;
                decoder.offset = start;
            }
            else
                decoder.state = DECODER_SYNC3;
            break;

        case DECODER_SYNC3:
            if(decoder.data_size >= sizeof(CommandHeader_t)) {
                uint8_t *buffer = decoder.buffer + decoder.offset;
                CommandHeader_t *header = (CommandHeader_t *) buffer;
                decoder.expected_size = sizeof(CommandHeader_t) + MIN(header->payload_size, COMMAND_PAYLOAD_MAX_SIZE_BYTES);
                decoder.state = DECODER_COMMAND_INCOMPLETE;
            }
            break;

        case DECODER_COMMAND_INCOMPLETE:
            if(decoder.data_size >= decoder.expected_size)
                done = true;
            break;

        case DECODER_COMMAND_COMPLETE:
            break;
        }
    }

    if(start > 1) {
        // If possible command starts in the middle of bufer, then shift buffer to fit it.
        command_shiftBuffer(decoder.buffer, decoder.data_size, size - 1);
    }

    return decoder.state;
}

CommandDecoderError_t commandDecoder_parse()
{
    decoder.state = DECODER_NO_COMMAND;
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
