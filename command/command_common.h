////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       15.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMMAND_COMMON_H
#define COMMAND_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define COMMANDS_VERSION                    "0.0.1"         ///< Commands protocol version. Used to recognize mismatches.
#define COMMANDS_MAX_SIZE_BYTES             1024            ///< Maximal size of command in total.

#define COMMANDS_SYNC_WORD_1                0x12345678      ///< First synchonizing word.
#define COMMANDS_SYNC_WORD_3                0x12345678      ///< Second synchonizing word.
#define COMMANDS_SYNC_WORD_2                0x12345678      ///< Third synchonizing word.

/// @brief Type of commands.
typedef enum {
    COMMAND_EMULATOR,               ///< Commands related to emulator (ex. GPIO status, PWM wave width).
    COMMAND_CONTROL,                ///< Commands sent by GroundStation or RC system to control flight (speed, pitch, yaw, etc...).
    COMMAND_TELEMETRY,              ///< All messages, that hold some telemetry data.
    COMMAND_SYS_STATUS,             ///< System status messages.
    COMMAND_DEBUG,                  ///< Debug messages. Should be disabled in release firmware.
    COMMAND_TYPE_COUNT              ///< Number of values is this enum. SHOULD BE LAST.
} CommandType_t;

/// @brief Command header.
typedef struct {
    uint32_t sync1;                 ///< First synchonizing word.
    uint32_t sync2;                 ///< Second synchonizing word.
    uint32_t sync3;                 ///< Third synchonizing word.
    uint16_t version_major;         ///< Major number of version.
    uint16_t version_minor;         ///< Minor number of version.
    uint16_t version_patch;         ///< Patch number of version.
    uint32_t command_id;            ///< Id number in sequence of commands. Each command should have id bigger than the last one by 1.
    CommandType_t type;             ///< Command type.
    uint8_t payload_size;           ///< Size of command payload.
    uint32_t payload_crc;           ///< CRC of payload.
} __attribute__((packed)) CommandHeader_t;

/// @brief Functor to be used before and after entering critical section.
/// @param [in] lock                Flag indicating, if we are entering of leaving critical section.
typedef void (*SynchronizationFunctor)(bool lock);

/// @brief Functor to be used to calculate CRC of data in buffer.
/// @param [in] buffer              Buffer with data, for which CRC should be calculated.
/// @param [in] size                Size of data buffer.
/// @return Calculated CRC.
typedef uint32_t (*CRCFunctor)(uint8_t *buffer, uint32_t size);

/// @brief Registers synchronization functor in commands framework.
/// @param [in] functor             Synchronization functor.
void command_registerSynchronizationFunctor(SynchronizationFunctor functor);

/// @brief Registers CRC functor in commands framework.
/// @param [in] functor             CRC functor.
void command_registerCRCFunctor(CRCFunctor functor);

/// @brief Enters critical section by calling synchronization primitive.
void command_enterCriticalSection();

/// @brief Leaves critical section by calling synchronization primitive.
void command_leaveCriticalSection();

uint32_t command_computeCRC(const uint8_t *buffer, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif
