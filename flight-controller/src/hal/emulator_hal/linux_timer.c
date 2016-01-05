//---------------------------------------------------------------------------------------------------------------
//
// Filename   : linux_timer.c
// Author     : Kuba Sejdak
// Created on : 04.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "linux_timer.h"

#include <stdint.h>

//---------------------------------------------------------------------------------------------------------------
// INTERFACE FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

void timer_activate(TimerHandle_t *handle)
{
    // TODO: implement.
}

void timer_deactivate(TimerHandle_t *handle)
{
    // TODO: implement.
}

uint32_t timer_getCounter(TimerHandle_t *handle __attribute__((unused)))
{
    // Empty.
    return 0;
}

void timer_setCounter(TimerHandle_t *handle __attribute__((unused)), uint32_t value __attribute__((unused)))
{
    // Empty.
}
