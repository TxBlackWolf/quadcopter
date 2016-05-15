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
#include "board_drivers_support.h"
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

    if(!console_init())
        return false;

    console_write("board: Console ready\n");
    
    if(!clock_initPeriodicTimer())
        return false;

    console_write("board: Periodic timer ready\n");

    board_showSystemClocks();

#if ACCELEROMETER_ENABLED
#endif

#if BAROMETER_ENABLED
#endif

#if BUZZER_ENABLED
#endif

#if CAMERA_ENABLED
#endif

#if ENGINES_ENABLED
    console_write("board: Initializing engines\n");
    if(!engines_init()) {
        console_write("board: Failed to initialize engines\n");
        return false;
    }

    console_write("board: Engines ready\n");
#endif

#if GYROSCOPE_ENABLED
#endif

#if LIGHTS_ENABLED
    console_write("board: Initializing lights\n");
    if(!strobe_init()) {
        console_write("board: Failed to initialize lights\n");
        return false;
    }

    console_write("board: Lights ready\n");
#endif

#if MAGNETOMETER_ENABLED
#endif

    console_write("board: Init procedure completed\n");
    return true;
}
