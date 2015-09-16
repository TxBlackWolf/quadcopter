//---------------------------------------------------------------------------------------------------------------
//
// Filename   : board.c
// Author     : Kuba Sejdak
// Created on : 23.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "board.h"
#include "board_drivers_support.h"
#include "console.h"
#include "drivers/engines/engine.h"
#include "drivers/lights/lights.h"

void panic(const char *format, ...)
{
    // TODO: implement as red user LED blinking + console write.
}

bool board_init()
{
    // TODO: init panic LED

    if(!console_init())
        return false;

#if ACCELEROMETER_ENABLED
#endif

#if BAROMETER_ENABLED
#endif

#if BUZZER_ENABLED
#endif

#if CAMERA_ENABLED
#endif

#if ENGINES_ENABLED
    if(!engines_init())
        return false;
#endif

#if GYROSCOPE_ENABLED
#endif

#if LIGHTS_ENABLED
    if(!strobe_init())
        return false;
#endif

#if MAGNETOMETER_ENABLED
#endif

    return true;
}
