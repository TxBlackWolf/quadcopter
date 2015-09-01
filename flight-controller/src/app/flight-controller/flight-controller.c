//---------------------------------------------------------------------------------------------------------------
//
// Filename   : flight-controller.c
// Author     : Kuba Sejdak
// Created on : 22.07.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "misc/version.h"
#include "board/board.h"
#include "board/console.h"
#include "drivers/lights/lights.h"

#include <stdbool.h>

void show_welcome_message()
{
    console_write("Hello World!\n");
}

int main()
{
    // TODO: check if this is reboot in emergency mode.

    if(!board_init())
        panic("Failed to initialize board.");

    show_welcome_message();

    while(true)
    {
        strobe_blink();
        console_write("");
    }

    return 0;
}
