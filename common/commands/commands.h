////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       15.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMMANDS_H
#define COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define COMMANDS_VERSION                    "0.0.1"     ///< Commands protocol version. Used to recognize mismatches.
#define COMMANDS_PAYLOAD_MAX_SIZE_BYTES     1024        ///< Maximal size of command payload.

/// @brief Possible errors, that can occure during command parsing.
typedef enum {
    PARSING_OK,                     ///< No error.
    PARSING_BAD_VERSION,            ///< Mismatch in protocol version.
    PARSING_PACKET_LOST,            ///< Expected id does not match actual one. Possible packet lost.
    PARSING_BAD_CRC,                ///< Invalid CRC.
    PARSING_UNSUPPORTED_TYPE,       ///< Command type not supported. Should not happen, if protocol version matches.
    PARSING_INVALID_DATA            ///< Generic payload error. Something went wrong, when parsing specific command data.
} CommandParsingError_t;

typedef enum {
    COMMAND_EMULATOR,               ///< Commands related to emulator (ex. GPIO status, PWM wave width).
    COMMAND_CONTROL,                ///< Commands sent by GroundStation or RC system to control flight (speed, pitch, yaw, etc...).
    COMMAND_TELEMETRY,              ///< All messages, that hold some telemetry data.
    COMMAND_SYS_STATUS,             ///< System status messages.
    COMMAND_DEBUG                   ///< Debug messages. Should be disabled in release firmware.
} CommandType_t;

/// @brief Command header.
typedef struct {
    uint16_t version_major;         ///< Major number of version.
    uint16_t version_minor;         ///< Minor number of version.
    uint16_t version_patch;         ///< Patch number of version.
    uint32_t command_id;            ///< Id number in sequence of commands. Each command should have id bigger than the last one by 1.
    CommandType_t type;             ///< Command type.
    uint8_t payload_size;           ///< Size of command payload.
    uint32_t payload_crc;           ///< CRC of payload.
} __attribute__((packed)) CommandHeader_t;

/// @brief Functor to be used to calculate CRC of data in buffer.
/// @param [in] buffer              Buffer with data, for which CRC should be calculated.
/// @param [in] size                Size of data buffer.
/// @return Calculated CRC.
typedef uint32_t (*CRCFunctor)(uint8_t *buffer, uint32_t size);

/// @brief Registers CRC functor in commands framework.
/// @param [in] functor             CRC functor.
/// @return None.
void command_registerCRCFunctor(CRCFunctor functor);

/// @brief Checks, if this message is compatible with this framework.
/// @param [in] header              Command header.
/// @return True if command is compatible, false otherwise.
bool command_checkVersion(CommandHeader_t *header);

/// @brief Checks, if this message is next in sequence order,
/// @param [in] header              Command header.
/// @return True if command has expected sequence id, false otherwise.
bool command_checkId(CommandHeader_t *header);

/// @brief Checks, if this command payload has correct CRC.
/// @param [in] buffer              Command payload buffer.
/// @param [in] size                Payload size.
/// @param [in] crc                 Expected CRC.
/// @return True if CRC is correct, false otherwise.
bool command_checkCRC(uint8_t *buffer, uint32_t size, uint32_t crc);

/// @brief Parses command header to recognize concrete command and call appropriate handler.
/// @param [in] buffer              Buffer with command data.
/// @return Parsing error code.
CommandParsingError_t command_parse(uint8_t *buffer);

#ifdef __cplusplus
}
#endif

#endif
