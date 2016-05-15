////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       04.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef EMULATOR_BOARD_PINOUT_H
#define EMULATOR_BOARD_PINOUT_H

#include "board/board_drivers_support.h"
#include "hal/emulator_hal/network_uart.h"

// Network console.
#define NETWORK_CONSOLE_IP                      "127.0.0.1"
#define NETWORK_CONSOLE_PORT                    12555

// Network commands.
#define NETWORK_COMMANDS_IP                     "127.0.0.1"
#define NETWORK_COMMANDS_PORT                   12556

#if ACCELEROMETER_ENABLED
// TODO: implement.
#endif

#if BAROMETER_ENABLED
// TODO: implement.
#endif

#if BUZZER_ENABLED
// TODO: implement.
#endif

#if CAMERA_ENABLED
// TODO: implement.
#endif

#if ENGINES_ENABLED
    // Front left.
    #define ENGINE_FRONT_LEFT_PORT              2
    #define ENGINE_FRONT_LEFT_PIN               4
    #define ENGINE_FRONT_LEFT_TIMER             0
    #define ENGINE_FRONT_LEFT_TIMER_CHANNEL     0

    // Front right.
    #define ENGINE_FRONT_RIGHT_PORT             2
    #define ENGINE_FRONT_RIGHT_PIN              5
    #define ENGINE_FRONT_RIGHT_TIMER            0
    #define ENGINE_FRONT_RIGHT_TIMER_CHANNEL    0

    // Rear left.
    #define ENGINE_REAR_LEFT_PORT               2
    #define ENGINE_REAR_LEFT_PIN                2
    #define ENGINE_REAR_LEFT_TIMER              0
    #define ENGINE_REAR_LEFT_TIMER_CHANNEL      0

    // Rear right.
    #define ENGINE_REAR_RIGHT_PORT              2
    #define ENGINE_REAR_RIGHT_PIN               1
    #define ENGINE_REAR_RIGHT_TIMER             0
    #define ENGINE_REAR_RIGHT_TIMER_CHANNEL     0
#endif

#if GYROSCOPE_ENABLED
// TODO: implement.
#endif

#if LIGHTS_ENABLED
    // Strobe.
    #define BLUE_STROBE_PORT                    4
    #define BLUE_STROBE_PIN                     15
#endif

#if MAGNETOMETER_ENABLED
// TODO: implement.
#endif

#endif
