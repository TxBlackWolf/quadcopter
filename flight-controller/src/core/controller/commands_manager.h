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

typedef struct {
    bool active_commands[COMMAND_TYPE_COUNT];
} CommandsManager_t;

bool commandsManager_init();
bool commandsManager_send(uint8_t *command, int size);

void commandsManager_enableEmulator(bool enabled);
void commandsManager_enableControl(bool enabled);
void commandsManager_enableTelemetry(bool enabled);
void commandsManager_enableSystemStatus(bool enabled);
void commandsManager_enableDebug(bool enabled);

bool commandsManager_isEmulatorEnabled();
bool commandsManager_isControlEnabled();
bool commandsManager_isTelemetryEnabled();
bool commandsManager_isSystemStatusEnabled();
bool commandsManager_isDebugEnabled();

#endif
