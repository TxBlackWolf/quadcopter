//---------------------------------------------------------------------------------------------------------------
//
// Filename   : printf_console.c
// Author     : Kuba Sejdak
// Created on : 04.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "printf_console.h"

#include <stdarg.h>
#include <stdio.h>

static bool console_initialized = false;

bool console_init()
{
    console_initialized = true;
    console_write("\n");

    return console_initialized;
}

int console_write(const char *format, ...)
{
    if(!console_initialized)
        return -1;

    va_list args;
    va_start(args, format);
    int ret = vprintf(format, args);
    va_end(args);

    return ret;
}
