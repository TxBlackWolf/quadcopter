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

/// @brief Command decoder meta data.
typedef struct {
    uint8_t *buffer;                ///< Internal decoder buffer. 
    int offset;                     ///< Current parsing offset.
    uint32_t data_size;             ///< Current size of data in buffer.
    uint32_t expected_size;         ///< Expected size of complete command (based on command header).
    bool id_initialized;            ///< If true, then field 'expected_id' is valid. Otherwise any id is considered as 'expected'.
    uint32_t expected_id;           ///< Next expected id of incoming command. Used to find packets losses.
    CommandDecoderState_t state;    ///< Current state of decoder. Represents what we've ALREADY parsed in this command.
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
            return i;
    }

    return -1;
}

void commandDecoder_init(uint8_t *buffer)
{
    decoder.buffer = buffer;
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

    int command_offset = 0;
    int current_offset = 0;
    while((uint32_t) current_offset < decoder.data_size) {
        switch(decoder.state) {
        case DECODER_NO_COMMAND:
            printf("DECODER_NO_COMMAND\n");
            fflush(stdout);
            current_offset = commandDecoder_findSync(current_offset, COMMAND_SYNC_BYTE_1); 
            if(current_offset < 0) {
                // No SYNC1 byte found, so all data in buffer is invalid.
                decoder.data_size = 0;
                return decoder.state;
            }

            command_offset = current_offset;
            ++current_offset;
            decoder.state = DECODER_SYNC1;
            break;

        case DECODER_SYNC1:
            printf("DECODER_SYNC1\n");
            fflush(stdout);
            if(decoder.buffer[current_offset] != COMMAND_SYNC_BYTE_2) {
                decoder.state = DECODER_NO_COMMAND;
                break;
            }

            ++current_offset;
            decoder.state = DECODER_SYNC2;
            break;

        case DECODER_SYNC2:
            printf("DECODER_SYNC2\n");
            fflush(stdout);
            if(decoder.buffer[current_offset] != COMMAND_SYNC_BYTE_3) {
                decoder.state = DECODER_NO_COMMAND;
                break;
            }

            ++current_offset;
            decoder.state = DECODER_SYNC3;
            break;

        case DECODER_SYNC3: {
            printf("DECODER_SYNC3\n");
            fflush(stdout);
            if((decoder.data_size - command_offset) < sizeof(CommandHeader_t))
                goto feed_exit;

            CommandHeader_t *header = (CommandHeader_t *) (decoder.buffer + command_offset);
            decoder.expected_size = sizeof(CommandHeader_t) + MIN(header->payload_size, COMMAND_PAYLOAD_MAX_SIZE_BYTES);
            decoder.state = DECODER_COMMAND_INCOMPLETE;
            break;
        }

        case DECODER_COMMAND_INCOMPLETE:
            printf("DECODER_COMMAND_INCOMPLETE\n");
            fflush(stdout);
            if((decoder.data_size - command_offset) < decoder.expected_size)
                goto feed_exit;

            decoder.state = DECODER_COMMAND_COMPLETE;
            break;

        case DECODER_COMMAND_COMPLETE:
            printf("DECODER_COMMAND_COMPLETE\n");
            fflush(stdout);
            goto feed_exit;
        }
    }

feed_exit:
    if (command_offset > 0) {
        // Command starts in the middle of the buffer. Align it to the beginning of the buffer.
        command_shiftBuffer(decoder.buffer, decoder.data_size, command_offset);
        decoder.data_size -= command_offset;
    }

    return decoder.state;
}

CommandDecoderError_t commandDecoder_parse()
{
    decoder.state = DECODER_NO_COMMAND;
    command_shiftBuffer(decoder.buffer, decoder.data_size, decoder.expected_size);
    decoder.data_size -= decoder.expected_size;
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
