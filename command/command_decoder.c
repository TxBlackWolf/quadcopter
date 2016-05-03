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
#include "command_statistics.h"

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
/// @return Difference between expected id and actual id. 
static int commandDecoder_checkId(CommandHeader_t *header)
{
    if(!decoder.id_initialized) {
        decoder.expected_id = header->command_id + 1;
        decoder.id_initialized = true;
        return 0; 
    }

    int diff = header->command_id - decoder.expected_id;
    decoder.expected_id = header->command_id + 1;
    return diff;
}

/// @brief Checks, if this message has correct CRC.
/// @param [in] buffer              Buffer with command (including header).
/// @return True if computed CRC matches one from header, false otherwise.
static bool commandDecoder_checkCRC(const uint8_t *buffer)
{
    CommandHeader_t *header = (CommandHeader_t *) buffer;
    const uint8_t *payload = buffer + sizeof(CommandHeader_t);
    uint32_t actual_crc = command_computeCRC(payload, header->payload_size);

    return (actual_crc == header->payload_crc);
}

/// @brief Looks for synchronization byte in internal buffer.
/// @return Position with synchronization byte.
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
            if(decoder.buffer[current_offset] != COMMAND_SYNC_BYTE_2) {
                decoder.state = DECODER_NO_COMMAND;
                break;
            }

            ++current_offset;
            decoder.state = DECODER_SYNC2;
            break;

        case DECODER_SYNC2:
            if(decoder.buffer[current_offset] != COMMAND_SYNC_BYTE_3) {
                decoder.state = DECODER_NO_COMMAND;
                break;
            }

            ++current_offset;
            decoder.state = DECODER_SYNC3;
            break;

        case DECODER_SYNC3: {
            if((decoder.data_size - command_offset) < sizeof(CommandHeader_t))
                goto feed_exit;

            CommandHeader_t *header = (CommandHeader_t *) (decoder.buffer + command_offset);
            decoder.expected_size = MIN(sizeof(CommandHeader_t) + header->payload_size, COMMAND_PAYLOAD_MAX_SIZE_BYTES);
            decoder.state = DECODER_COMMAND_INCOMPLETE;
            break;
        }

        case DECODER_COMMAND_INCOMPLETE:
            if((decoder.data_size - command_offset) < decoder.expected_size)
                goto feed_exit;

            decoder.state = DECODER_COMMAND_COMPLETE;
            break;

        case DECODER_COMMAND_COMPLETE:
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
    CommandHeader_t *header = (CommandHeader_t *) decoder.buffer;
    commandStatistics_markReceived();

    CommandDecoderError_t result = PARSING_OK;
    if(!commandDecoder_checkVersion(header)) {
        commandStatistics_markBroken();
        result = PARSING_BAD_VERSION;
        goto parse_exit;
    }
    
    int diff = commandDecoder_checkId(header);
    if(diff > 0)
        commandStatistics_markLost(diff);

    //if(!commandDecoder_checkCRC(decoder.buffer)) {
    //    commandStatistics_markBroken();
    //    return PARSING_BAD_CRC;
    //}

    switch(header->type) {
    case COMMAND_EMULATOR:
        result = command_parseEmulator(decoder.buffer + sizeof(CommandHeader_t), header->payload_size);
        break;
    case COMMAND_CONTROL:
    case COMMAND_TELEMETRY:
    case COMMAND_SYS_STATUS:
    case COMMAND_DEBUG:
    default:
        result = PARSING_UNSUPPORTED_TYPE;
        break;
    }

    if(result != PARSING_OK)
        commandStatistics_markBroken();

parse_exit:
    decoder.state = DECODER_NO_COMMAND;
    command_shiftBuffer(decoder.buffer, decoder.data_size, decoder.expected_size);
    decoder.data_size -= decoder.expected_size;

    return result;
}
