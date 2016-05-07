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

#define COMMAND_VERSION                     "0.0.2"   ///< Commands protocol version. Used to recognize mismatches.
#define COMMAND_MAX_SIZE_BYTES              1024      ///< Maximal size of command in total.
#define COMMAND_PAYLOAD_MAX_SIZE_BYTES      (COMMAND_MAX_SIZE_BYTES - sizeof(CommandHeader_t))

#define COMMAND_SYNC_BYTE_1                 0x48      ///< First synchonizing byte.
#define COMMAND_SYNC_BYTE_2                 0x69      ///< Second synchonizing byte.
#define COMMAND_SYNC_BYTE_3                 0xa5      ///< Third synchonizing byte.

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
    uint8_t sync1;                  ///< First synchonizing byte.
    uint8_t sync2;                  ///< Second synchonizing byte.
    uint8_t sync3;                  ///< Third synchonizing byte.
    uint16_t version_major;         ///< Major number of version.
    uint16_t version_minor;         ///< Minor number of version.
    uint16_t version_patch;         ///< Patch number of version.
    uint32_t command_id;            ///< Id number in sequence of commands. Each command should have id bigger than the last one by 1.
    CommandType_t type;             ///< Command type.
    uint32_t payload_size;          ///< Size of command payload.
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

/// @brief Get version major from version string.
/// @return Version major.
uint16_t command_getVersionMajor();

/// @brief Get version minor from version string.
/// @return Version minor.
uint16_t command_getVersionMinor();

/// @brief Get version patch from version string.
/// @return Version patch.
uint16_t command_getVersionPatch();

/// @Brief Computes CRC for given buffer and size.
/// @param [in] buffer              Buffer with data, for which CRC should be calculated.
/// @param [in] size                Size of data buffer.
/// @return Calculated CRC.
uint32_t command_computeCRC(const uint8_t *buffer, uint32_t size);

/// @brief Copies data from one buffer to another,
/// @param [in] to                  Destination buffer.
/// @param [in] from                Source buffer.
/// @param [in] size                Size of data to be copied.
void command_copyBuffer(uint8_t *to, const uint8_t *from, int size);

/// @brief Shifts left given buffer. 
/// @param [in] buffer              Buffer to be shifter
/// @param [in] size                Buffer size.
/// @param [in] positions           Shift size.
void command_shiftBuffer(uint8_t *buffer, int size, int positions);

/// @brief Converts string to integer.
/// @param [in] str                 String to be converted.
/// @param [in] size                Size of string.
/// @return Integer representation of given string.
int command_atoi(char *str, int size);

#ifdef __cplusplus
}
#endif

#endif
