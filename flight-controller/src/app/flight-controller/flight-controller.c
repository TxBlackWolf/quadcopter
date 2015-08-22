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
#include "board/console.h"
#include "drivers/lights/lights.h"

#include <stdbool.h>

void show_welcome_message()
{
    console_write("Hello World!\n");
}

int main()
{
    if(!console_init())
    {
    }

    show_welcome_message();
    strobe_init();

    while(true)
    {
        strobe_blink();
        volatile int i;
        for(i = 0; i < 10000000; ++i);
    }

    return 0;
}
