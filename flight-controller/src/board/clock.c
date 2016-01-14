//=============================================================================================
//
// Filename   : clock.c
// Author     : Kuba Sejdak
// Created on : 05.12.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#include "clock.h"
#include "assert.h"
#include "board.h"
#include "console.h"
#include "hal/timer.h"
#include "utils/misc/minmax.h"

#include <limits.h>
#include <stdlib.h>

#define CLOCK_MAX_PERIODIC_EVENTS_COUNT     5

typedef struct {
    ClockEventCallback_t callback;
    uint32_t period_ms;
    uint32_t deadline_ms;
    int32_t count;
} PeriodicEvent_t;

TimerHandle_t periodic_timer_handle;

static PeriodicEvent_t periodic_events[CLOCK_MAX_PERIODIC_EVENTS_COUNT];
uint32_t earliest_deadline_ms = 0;
uint32_t tick_counter_ms = 0;

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
    clock_updateEventsDeadline();

    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback != NULL)
            continue;

        periodic_events[i].callback = callback;
        periodic_events[i].period_ms = period_ms;
        periodic_events[i].deadline_ms = period_ms;
        periodic_events[i].count = count;

        if(earliest_deadline_ms > periodic_events[i].deadline_ms || earliest_deadline_ms == 0)
            earliest_deadline_ms = periodic_events[i].deadline_ms;

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

        clock_removePeriodicEvent(i);
        clock_updateEarliestDeadline();
        return true;
    }

    return false;
}

void clock_removePeriodicEvent(int index)
{
    periodic_events[index].callback = NULL;
    periodic_events[index].period_ms = 0;
    periodic_events[index].deadline_ms = 0;
    periodic_events[index].count = 0;
}

void clock_updateEventsDeadline()
{
    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback == NULL)
            continue;

        periodic_events[i].deadline_ms -= tick_counter_ms;
    }

    earliest_deadline_ms -= tick_counter_ms;
    tick_counter_ms = 0;
}

void clock_updateEarliestDeadline()
{
    uint32_t next_earliest_deadline_ms = UINT32_MAX;
    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback == NULL)
            continue;

        next_earliest_deadline_ms = MIN(next_earliest_deadline_ms, periodic_events[i].deadline_ms);
    }

    earliest_deadline_ms = (next_earliest_deadline_ms != UINT32_MAX) ? next_earliest_deadline_ms : 0;
}

void clock_processPeriodicEvents()
{
    if(earliest_deadline_ms == 0)
        return;

    ++tick_counter_ms;
    if(tick_counter_ms < earliest_deadline_ms)
        return;

    timer_deactivate(&periodic_timer_handle);
    clock_updateEventsDeadline();

    // Launch & remove all callbacks, that expired.
    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback == NULL)
            continue;

        if(periodic_events[i].deadline_ms != 0)
            continue;

        // Launch event callback.
        board_assert(periodic_events[i].callback);
        periodic_events[i].callback();

        // Restore event deadline.
        periodic_events[i].deadline_ms = periodic_events[i].period_ms;

        if(periodic_events[i].count == -1) {
            // This is an infinite periodic event.
            continue;
        }

        periodic_events[i].count--;
        if(periodic_events[i].count == 0)
            clock_removePeriodicEvent(i);
    }

    clock_updateEarliestDeadline();
    timer_activate(&periodic_timer_handle);
}
