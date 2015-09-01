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
#include "drivers/lights/lights.h"

void panic(const char *format, ...)
{
    // TODO: implement as red user LED blinking.
}

bool board_init()
{
    // TODO: init panic LED

    if(!console_init())
        return false;

#if LIGHTS_ENABLED
    if(!strobe_init())
        return false;
#endif

    return true;
}
