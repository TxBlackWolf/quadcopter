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
typedef uint8_t TimerChannel_t;

// Timer handle.
typedef struct {
    TimerDevice_t device;
    TimerChannel_t channel;
} TimerHandle_t;

// General timer event callback.
typedef void (*TimerEventCallback_t)(void);

void timer_activate(TimerHandle_t *handle);
void timer_deactivate(TimerHandle_t *handle);

bool timer_registerEventCallback(TimerHandle_t *handle, TimerEventCallback_t callback);

uint32_t timer_getCounter(TimerHandle_t *handle);
void timer_setCounter(TimerHandle_t *handle, uint32_t value);

#endif
