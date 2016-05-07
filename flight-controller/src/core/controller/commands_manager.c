////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       10.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "commands_manager.h"
#include "board/board.h"
#include "board/console.h"
#include "hal/uart.h"

static CommandsManagerSettings_t manager_settings;
static UARTHandle_t uart_handle;

bool commandsManager_init()
{
    commandsManager_enableEmulator(board_isEmulator());
    commandsManager_enableControl(true);
    commandsManager_enableTelemetry(true);
    commandsManager_enableSystemStatus(true);
    commandsManager_enableDebug(board_isDebug());

    if(!board_commandsInit(&uart_handle))
        console_write("Failed to initialize commands communication link. Commands may not work now\n");

    return true;
}

bool commandsManager_send(uint8_t *command, int size)
{
    for(int i = 0; i < size; ++i) {
        if(!uart_send(&uart_handle, command[i]))
            return false;
    }

    return true;
}

void commandsManager_enableEmulator(bool enabled)
{
    manager_settings.supported_commands[COMMAND_EMULATOR] = enabled;
    console_write("%s support for emulator commands\n", enabled ? "Enabled" : "Disabled");
}

void commandsManager_enableControl(bool enabled)
{
    manager_settings.supported_commands[COMMAND_CONTROL] = enabled;
    console_write("%s support for control commands\n", enabled ? "Enabled" : "Disabled");
}

void commandsManager_enableTelemetry(bool enabled)
{
    manager_settings.supported_commands[COMMAND_TELEMETRY] = enabled;
    console_write("%s support for telemetry commands\n", enabled ? "Enabled" : "Disabled");
}

void commandsManager_enableSystemStatus(bool enabled)
{
    manager_settings.supported_commands[COMMAND_SYS_STATUS] = enabled;
    console_write("%s support for system status commands\n", enabled ? "Enabled" : "Disabled");
}

void commandsManager_enableDebug(bool enabled)
{
    manager_settings.supported_commands[COMMAND_DEBUG] = enabled;
    console_write("%s support for debug commands\n", enabled ? "Enabled" : "Disabled");
}

bool commandsManager_isEmulatorEnabled()
{
    return manager_settings.supported_commands[COMMAND_EMULATOR];
}

bool commandsManager_isControlEnabled()
{
    return manager_settings.supported_commands[COMMAND_CONTROL];
}

bool commandsManager_isTelemetryEnabled()
{
    return manager_settings.supported_commands[COMMAND_TELEMETRY];
}

bool commandsManager_isSystemStatusEnabled()
{
    return manager_settings.supported_commands[COMMAND_SYS_STATUS];
}

bool commandsManager_isDebugEnabled()
{
    return manager_settings.supported_commands[COMMAND_DEBUG];
}
