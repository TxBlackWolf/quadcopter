////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       27.06.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "system_status.h"
#include "utils/version.h"
#include "board/board.h"

#include <stdio.h>

static SystemStatus_t system_status;

void systemStatus_init()
{
    // Info about compiled firmware.
    system_status.firmware_name = FIRMWARE_NAME;
    system_status.firmware_version = FIRMWARE_VERSION;
    system_status.is_debug = board_isDebug();
    system_status.is_emulator = board_isEmulator();

    system_status.boot_completed = false;

    system_status.engines_name = NULL;
}

void systemStatus_bootingCompleted()
{
    system_status.boot_completed = true;
}

void systemStatus_setEnginesName(const char *name)
{
    system_status.engines_name = name;
}
