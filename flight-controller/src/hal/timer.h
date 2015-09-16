//---------------------------------------------------------------------------------------------------------------
//
// Filename   : timer.h
// Author     : Kuba Sejdak
// Created on : 05.09.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef TIMER_H
#define TIMER_H

#include "gpio.h"

#include <stdint.h>

typedef uint32_t TimerDevice_t;

// Timer handle.
typedef struct
{
    TimerDevice_t timer_device;
} TimerHandle_t;

void timer_activate(TimerDevice_t device);
void timer_deactivate(TimerDevice_t device);

uint32_t timer_getCounter(TimerDevice_t device);
void timer_setCounter(TimerDevice_t device, uint32_t value);

#endif
