//---------------------------------------------------------------------------------------------------------------
//
// Filename   : clock.c
// Author     : Kuba Sejdak
// Created on : 05.12.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "clock.h"
#include "board.h"
#include "board/console.h"
#include "hal/timer.h"
#include "utils/misc/minmax.h"

#include <stdlib.h>
#include <limits.h>

#define CLOCK_MAX_PERIODIC_EVENTS_COUNT     5

typedef struct {
    ClockEventCallback_t callback;
    uint32_t period_ms;
    uint32_t correction_ms;
    int32_t count;
    bool just_added;
} PeriodicEvent_t;

TimerHandle_t periodic_timer_handle;

static PeriodicEvent_t periodic_events[CLOCK_MAX_PERIODIC_EVENTS_COUNT];
uint32_t minimal_period = 0;
uint32_t period_counter = 0;

bool clock_initPeriodicTimer()
{
    return board_initPeriodicTimer(&periodic_timer_handle);
}

bool clock_addPeriodicCallback(ClockEventCallback_t callback, uint32_t period_ms, int32_t count)
{
    timer_deactivate(&periodic_timer_handle);
    bool ret = clock_addPeriodicCallbackAsync(callback, period_ms, count);
    timer_activate(&periodic_timer_handle);

    return ret;
}

bool clock_addPeriodicCallbackAsync(ClockEventCallback_t callback, uint32_t period_ms, int32_t count)
{
    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback != NULL)
            continue;

        periodic_events[i].callback = callback;
        periodic_events[i].period_ms = period_ms;
        periodic_events[i].count = count;
        periodic_events[i].correction_ms = period_counter;
        periodic_events[i].just_added = true;

        if(minimal_period > period_ms || minimal_period == 0)
            minimal_period = period_ms;

        return true;
    }

    console_write("board: Failed to find empty slot for periodic event!\n");
    return false;
}

bool clock_removePeriodicCallback(ClockEventCallback_t callback)
{
    timer_deactivate(&periodic_timer_handle);
    bool ret = clock_removePeriodicCallbackAsync(callback);
    timer_activate(&periodic_timer_handle);

    return ret;
}

bool clock_removePeriodicCallbackAsync(ClockEventCallback_t callback)
{
    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback != callback)
            continue;

        periodic_events[i].callback = NULL;
        periodic_events[i].period_ms = 0;
        periodic_events[i].correction_ms = 0;
        periodic_events[i].count = 0;
        return true;
    }

    return false;
}

void clock_processPeriodicEvents()
{
    if(minimal_period == 0)
        return;

    ++period_counter;
    if(period_counter < minimal_period)
        return;

    timer_deactivate(&periodic_timer_handle);

    period_counter = 0;

    // Launch & remove all callbacks, that expired.
    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback == NULL)
            continue;

        if(periodic_events[i].just_added)
            continue;

        if(periodic_events[i].period_ms != minimal_period)
            continue;

        periodic_events[i].callback();

        if(periodic_events[i].count == -1) {
            // This is infinite periodic event.
            continue;
        }

        periodic_events[i].count--;
        if(periodic_events[i].count == 0) {
            // Remove this event.
            periodic_events[i].callback = NULL;
            periodic_events[i].period_ms = 0;
            periodic_events[i].correction_ms = 0;
            periodic_events[i].count = 0;
            continue;
        }
    }

    // Update remaining time for existing events.
    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback == NULL)
            continue;

        if(periodic_events[i].just_added && periodic_events[i].correction_ms == 0)
            continue;

        periodic_events[i].period_ms -= (minimal_period - periodic_events[i].correction_ms);
        periodic_events[i].correction_ms = 0;
    }

    // Find smallest period.
    uint32_t next_minimal_period = UINT32_MAX;
    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback == NULL)
            continue;

        periodic_events[i].just_added = false;
        next_minimal_period = MIN(next_minimal_period, periodic_events[i].period_ms);
    }

    minimal_period = (next_minimal_period != UINT32_MAX) ? next_minimal_period : 0;
    timer_activate(&periodic_timer_handle);
}
