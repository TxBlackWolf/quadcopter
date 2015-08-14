//---------------------------------------------------------------------------------------------------------------
//
// Filename   : FlightController.c
// Author     : Kuba Sejdak
// Created on : 22.07.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "Misc/Version.h"
#include "Platform/Console.h"

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

    // Main program loop.
    while(true)
    {
        if(c == 100000)
        {
            c = 0;
            console_write("0");
        }

        console_write("1");
    }

    return 0;
}
