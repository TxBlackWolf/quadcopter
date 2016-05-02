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

#include <stdbool.h>
#include <stdint.h>

/// @brief Possible decode states.
typedef enum {
    DECODER_NO_COMMAND,             ///< No start of command is found inside buffer.
    DECODER_SYNC1,                  ///< Sync1 value is recognized.
    DECODER_SYNC2,                  ///< Sync2 value is recognized.
    DECODER_SYNC3,                  ///< Sync3 value is recognized.
    DECODER_COMMAND_INCOMPLETE,     ///< Command header is recognized, but there is less data, than declared payload size.
    DECODER_COMMAND_COMPLETE        ///< Command is complete and can be parsed.
} CommandDecoderState_t;

/// @brief Possible parsing errors.
typedef enum {
    PARSING_OK,                     ///< No error.
    PARSING_BAD_VERSION,            ///< Mismatch in protocol version.
    PARSING_BAD_CRC,                ///< Invalid CRC.
    PARSING_UNSUPPORTED_TYPE,       ///< Command type not supported. Should not happen, if protocol version matches.
    PARSING_INVALID_DATA            ///< Generic payload error. Something went wrong, when parsing specific command data.
} CommandDecoderError_t;

/// @brief Initializes internal framework buffer for keeping incoming data until it is parsed.
/// @param [in] buffer              Buffer for incoming data.
void commandDecoder_init(uint8_t *buffer);

/// @brief Copies data into internal buffer.
/// @note This function should always leave buffer aligned to first SYNC byte or to the beginning. Parser state allow to distinguish those situations.. 
/// @param [in] buffer              Data buffer.
/// @param [in] size                Data size.
/// @return Decoder state.
CommandDecoderState_t commandDecoder_feed(const uint8_t *buffer, int size);

/// @brief Parses command header to recognize concrete command and call appropriate handler.
/// @return Parsing error code.
CommandDecoderError_t commandDecoder_parse();

#ifdef __cplusplus
}
#endif

#endif
