////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       10.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMMANDS_MANGER_H
#define COMMANDS_MANGER_H

#include "command/command_common.h"

#include <stdbool.h>
#include <stdint.h>

/// @brief Command manager meta data.
typedef struct {
    bool active_commands[COMMAND_TYPE_COUNT];           ///< Flags indicating if particular command is enabled.
    uint8_t buffer[2 * COMMAND_MAX_SIZE_BYTES];         ///< Buffer for receiving commands' data.
} CommandsManager_t;

/// @brief Initializes commands manager and commmands framework.
/// @return True on success, false otherwise.
bool commandsManager_init();

/// @brief Sends command, that is located in given buffer.
/// @param [in] command             Buffer with command to be sent.
/// @param [in] size                Size of data in given buffer.
/// @return True on success, false otherwise.
bool commandsManager_send(uint8_t *command, int size);

/// @brief Reads data from UART device and feeds command parser with it.
///        If parser indicates, that commmand is complete, it calls command processing function.
void commandsManager_receive();

/// @brief Enables/disables emulator commands subsystem.
/// @param [in] enabled             Flag indicating if subsystem should be enabled or disabled.
void commandsManager_enableEmulator(bool enabled);

/// @brief Enables/disables control commands subsystem.
/// @param [in] enabled             Flag indicating if subsystem should be enabled or disabled.
void commandsManager_enableControl(bool enabled);

/// @brief Enables/disables telemetry commands subsystem.
/// @param [in] enabled             Flag indicating if subsystem should be enabled or disabled.
void commandsManager_enableTelemetry(bool enabled);

/// @brief Enables/disables system status commands subsystem.
/// @param [in] enabled             Flag indicating if subsystem should be enabled or disabled.
void commandsManager_enableSystemStatus(bool enabled);

/// @brief Enables/disables debug commands subsystem.
/// @param [in] enabled             Flag indicating if subsystem should be enabled or disabled.
void commandsManager_enableDebug(bool enabled);

/// @brief Checks if give command subsystem is enabled.
/// @param [in] type                Type of command to be checked.
/// @return True if subsystem is enabled, false otherwise.
bool commandsManager_isEnabled(CommandType_t type);

#endif
