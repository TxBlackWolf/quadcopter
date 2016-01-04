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
#include "hal/timer.h"

#include <stdint.h>

//---------------------------------------------------------------------------------------------------------------
// INTERFACE FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

void timer_activate(TimerHandle_t *handle)
{
}

void timer_deactivate(TimerHandle_t *handle)
{
}

uint32_t timer_getCounter(TimerHandle_t *handle)
{
}

void timer_setCounter(TimerHandle_t *handle, uint32_t value)
{
}
