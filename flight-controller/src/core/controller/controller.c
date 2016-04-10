////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       10.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "controller.h"
#include "board/console.h"
#include "commands_manager.h"

#include <stdbool.h>

int controller_run()
{
    commandsManager_init();
    console_write("Initialized commands manager.\n");

    while(true);

    return 0;
}
