////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       23.08.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "board.h"
#include "clock.h"
#include "console.h"
#include "drivers/engines/engine.h"
#include "drivers/lights/lights.h"

void panic(const char *format __attribute__((unused)), ...)
{
    /// @todo Implement.
    // 1) when in debug moge - red user led ON + console write + CPU halt
    // 2) when in release mode - red user led ON (permanent) + console write + CPU restart
}

bool board_isDebug()
{
#ifdef NDEBUG
    return false;
#else
    return true;
#endif
}

bool board_init()
{
    /// @todo Init panic LED.

    if (!console_init())
        return false;

    console_write("board: Console initialized\n");

    console_write("board: Initializing periodic timer\n");    
    if (!clock_initPeriodicTimer()) {
        console_write("board: Failed to initialize periodic timer\n");
        return false;
    }

    board_showSystemClocks();

    // Initialize drivers.
    console_write("board: Initializing engines\n");
    if (!engines_init()) {
        console_write("board: Failed to initialize engines\n");
        return false;
    }

    console_write("board: Initializing lights\n");
    if (!strobe_init()) {
        console_write("board: Failed to initialize lights\n");
        return false;
    }

    console_write("board: Init procedure completed\n");
    return true;
}
