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

void panic()
{
    // TODO: implement as red user LED blinking.
}

int main()
{
    if(!board_init())
        panic();

    show_welcome_message();

    while(true)
    {
        strobe_blink();
    }

    return 0;
}
