////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       22.07.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "board/board.h"
#include "board/console.h"
#include "core/controller/controller.h"
#include "utils/version.h"

#include <stdbool.h>

/// @brief Prints welcome message along with firmware info.
/// @return None
void show_welcome_message()
{
    console_write("\n");
    console_write("                   Welcome to                \n");
    console_write("   _____ _       __      ___                 \n");
    console_write("  / ____| |      \\ \\    / (_)                \n");
    console_write(" | (___ | | ___   \\ \\  / / _ _ __   ___ _ __ \n");
    console_write("  \\___ \\| |/ / | | \\ \\/ / | | '_ \\ / _ \\ '__|\n");
    console_write("  ____) |   <| |_| |\\  /  | | |_) |  __/ |   \n");
    console_write(" |_____/|_|\\_\\\\__, | \\/   |_| .__/ \\___|_|   \n");
    console_write("               __/ |        | |              \n");
    console_write("              |___/         |_|              \n");
    console_write("                     drone                   \n");
    console_write("\n");

    console_write("System info:\n");
    console_write("Device name     : %s\n", DEVICE_NAME);
    console_write("Device version  : %s\n", DEVICE_VERSION);
    console_write("Firmware name   : %s\n", FIRMWARE_NAME);
    console_write("Firmware version: %s\n", FIRMWARE_VERSION);
    console_write("Firmware author : %s\n", FIRMWARE_AUTHOR);
    console_write("Contact info    : %s\n", CONTACT_INFO);
    console_write("\n");
}

/// @brief Main program function.
/// @return Should never return.
int main()
{
    if(board_isEmergencyBoot()) {
        /// @todo React in a proper way.
    }

    if(!board_init())
        panic("Failed to initialize board.");

    show_welcome_message();

    return controller_run();
}
