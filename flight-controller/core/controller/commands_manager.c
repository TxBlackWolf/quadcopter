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
#include "command/command_decoder.h"
#include "hal/uart.h"

// @todo Only for test.
#include "command/command_control.h"

#include <stdio.h>

static CommandsManager_t manager_settings;
static UARTHandle_t uart_handle;

void throttle_cb(uint8_t *buffer, uint32_t size)
{
    ControlCommandThrottle_t *throttle_command = (ControlCommandThrottle_t *) buffer;
    console_write("throttle: %d %%\n", throttle_command->throttle);
}

bool commandsManager_init()
{
    commandDecoder_init(manager_settings.buffer);

    commandsManager_enableEmulator(board_isEmulator());
    commandsManager_enableControl(true);
    commandsManager_enableTelemetry(true);
    commandsManager_enableSystemStatus(true);
    commandsManager_enableDebug(board_isDebug());

    if (!board_commandsInit(&uart_handle, commandsManager_receive))
        console_write("Failed to initialize commands communication link. Commands will not work\n");

    console_write("Configured commands receive buffer and communication link\n");

    // @todo Only for test.
    command_registerControlCallback(CONTROL_EVENT_THROTTLE, throttle_cb);
    return true;
}

bool commandsManager_send(uint8_t *command, int size)
{
    for (int i = 0; i < size; ++i) {
        if (!uart_send(&uart_handle, command[i]))
            return false;
    }

    return true;
}

void commandsManager_receive()
{
    uint16_t data;
    if (!uart_receive(&uart_handle, &data))
        return;

    uint8_t byte = (uint8_t) data;
    if (commandDecoder_feed(&byte, 1) != DECODER_COMMAND_COMPLETE)
        return;

    CommandType_t commandType;
    commandDecoder_checkType(&commandType);
    if (!commandsManager_isEnabled(commandType)) {
        commandDecoder_drop();
        return;
    }

    commandDecoder_parse(NULL);
}

void commandsManager_enableEmulator(bool enabled)
{
    manager_settings.active_commands[COMMAND_EMULATOR] = enabled;
    console_write("%s support for emulator commands\n", enabled ? "Enabled" : "Disabled");
}

void commandsManager_enableControl(bool enabled)
{
    manager_settings.active_commands[COMMAND_CONTROL] = enabled;
    console_write("%s support for control commands\n", enabled ? "Enabled" : "Disabled");
}

void commandsManager_enableTelemetry(bool enabled)
{
    manager_settings.active_commands[COMMAND_TELEMETRY] = enabled;
    console_write("%s support for telemetry commands\n", enabled ? "Enabled" : "Disabled");
}

void commandsManager_enableSystemStatus(bool enabled)
{
    manager_settings.active_commands[COMMAND_SYS_STATUS] = enabled;
    console_write("%s support for system status commands\n", enabled ? "Enabled" : "Disabled");
}

void commandsManager_enableDebug(bool enabled)
{
    manager_settings.active_commands[COMMAND_DEBUG] = enabled;
    console_write("%s support for debug commands\n", enabled ? "Enabled" : "Disabled");
}

bool commandsManager_isEnabled(CommandType_t type)
{
    return manager_settings.active_commands[type];
}
