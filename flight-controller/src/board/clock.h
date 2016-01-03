//---------------------------------------------------------------------------------------------------------------
//
// Filename   : clock.h
// Author     : Kuba Sejdak
// Created on : 05.12.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef CLOCK_H
#define CLOCK_H

#include <stdbool.h>
#include <stdint.h>

#define CLOCK_PERIODIC_TIMER_PERIOD_MS      1

// General clock event callback.
typedef void (*ClockEventCallback_t)(void);

bool clock_initPeriodicTimer();

bool clock_addPeriodicCallback(ClockEventCallback_t callback, uint32_t period_ms, int32_t count);
bool clock_addPeriodicCallbackAsync(ClockEventCallback_t callback, uint32_t period_ms, int32_t count);
bool clock_removePeriodicCallback(ClockEventCallback_t callback);
bool clock_removePeriodicCallbackAsync(ClockEventCallback_t callback);
void clock_removePeriodicEvent(int index);

void clock_updateEventsDeadline();
void clock_updateEarliestDeadline();

void clock_processPeriodicEvents();

#endif
