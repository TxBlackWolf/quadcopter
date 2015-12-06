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
#include "board/console.h"

#include <stdlib.h>

#define CLOCK_MAX_PERIODIC_EVENTS_COUNT     5

typedef struct {
    ClockEventCallback_t callback;
    uint32_t period_ms;
    int32_t count;
} PeriodicEvent_t;

static PeriodicEvent_t periodic_events[CLOCK_MAX_PERIODIC_EVENTS_COUNT];
uint32_t minimal_period = 0;
uint32_t period_counter = 0;

bool clock_addPeriodicCallback(ClockEventCallback_t callback, uint32_t period_ms, int32_t count)
{
    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback != NULL)
            continue;

        periodic_events[i].callback = callback;
        periodic_events[i].period_ms = period_ms;
        periodic_events[i].count = count;

        if(minimal_period > period_ms)
            minimal_period = period_ms;

        return true;
    }

    console_write("board: Failed to find empty slot for periodic event!\n");
    return false;
}

bool clock_removePeriodicCallback(ClockEventCallback_t callback)
{
    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback != callback)
            continue;

        periodic_events[i].callback = NULL;
        periodic_events[i].period_ms = 0;
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

    period_counter = 0;

    uint32_t next_minimal_period = UINT32_MAX;

    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback == NULL)
            continue;

        if(periodic_events[i].period_ms != minimal_period) {
            periodic_events[i].period_ms -= minimal_period;
            if(periodic_events[i].period_ms < next_minimal_period)
                next_minimal_period = periodic_events[i].period_ms;

            continue;
        }

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
            periodic_events[i].count = 0;
            continue;
        }

    }

    if(next_minimal_period == UINT32_MAX)
        minimal_period = 0;
}
