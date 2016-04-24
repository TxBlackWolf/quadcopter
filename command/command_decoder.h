////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       23.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMMAND_DECODER_H
#define COMMAND_DECODER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "command_common.h"

#include <stdbool.h>
#include <stdint.h>

/// @brief Possible errors and states, that can occure during command parsing.
typedef enum {
    PARSING_OK,                     ///< No error.
    PARSING_BUFFERED,               ///< Command is not complete.
    PARSING_BAD_VERSION,            ///< Mismatch in protocol version.
    PARSING_PACKET_LOST,            ///< Expected id does not match actual one. Possible packet lost.
    PARSING_BAD_CRC,                ///< Invalid CRC.
    PARSING_UNSUPPORTED_TYPE,       ///< Command type not supported. Should not happen, if protocol version matches.
    PARSING_INVALID_DATA            ///< Generic payload error. Something went wrong, when parsing specific command data.
} CommandParsingStatus_t;

/// @brief Checks, if this message is next in sequence order,
/// @param [in] header              Command header.
/// @return True if command has expected sequence id, false otherwise.
bool commandDecoder_checkId(CommandHeader_t *header);

/// @brief Checks, if this command payload has correct CRC.
/// @param [in] buffer              Command payload buffer.
/// @param [in] size                Payload size.
/// @param [in] crc                 Expected CRC.
/// @return True if CRC is correct, false otherwise.
bool commandDecoder_checkCRC(const uint8_t *buffer, uint32_t size, uint32_t crc);

/// @brief Checks, if this message is compatible with this framework.
/// @param [in] header              Command header.
/// @return True if command is compatible, false otherwise.
bool command_checkVersion(CommandHeader_t *header);

/// @brief Parses command header to recognize concrete command and call appropriate handler.
/// @param [in] buffer              Buffer with command data.
/// @return Parsing error code.
CommandParsingStatus_t commandDecoder_parse(const uint8_t *buffer);

#ifdef __cplusplus
}
#endif

#endif
