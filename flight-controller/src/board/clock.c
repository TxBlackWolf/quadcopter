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

#include <stdlib.h>

#define CLOCK_MAX_PERIODIC_EVENTS_COUNT     5

typedef struct {
    ClockEventCallback_t callback;
    uint32_t period_ms;
    uint32_t correction_ms;
    int32_t count;
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
    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback != NULL)
            continue;

        periodic_events[i].callback = callback;
        periodic_events[i].period_ms = period_ms;
        periodic_events[i].count = count;
        periodic_events[i].correction_ms = period_counter;

        if(minimal_period > period_ms)
            minimal_period = period_ms;

        timer_activate(&periodic_timer_handle);
        return true;
    }

    timer_activate(&periodic_timer_handle);
    console_write("board: Failed to find empty slot for periodic event!\n");
    return false;
}

bool clock_removePeriodicCallback(ClockEventCallback_t callback)
{
    timer_deactivate(&periodic_timer_handle);
    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback != callback)
            continue;

        periodic_events[i].callback = NULL;
        periodic_events[i].period_ms = 0;
        periodic_events[i].count = 0;
        timer_activate(&periodic_timer_handle);
        return true;
    }

    timer_activate(&periodic_timer_handle);
    return false;
}

void clock_processPeriodicEvents()
{
    if(minimal_period == 0)
        return;

    ++period_counter;
    if(period_counter < minimal_period)
        return;

    uint32_t next_minimal_period = UINT32_MAX;

    for(int i = 0; i < CLOCK_MAX_PERIODIC_EVENTS_COUNT; ++i) {
        if(periodic_events[i].callback == NULL)
            continue;

        if(periodic_events[i].period_ms != minimal_period) {
            periodic_events[i].period_ms -= (minimal_period - periodic_events[i].correction_ms);
            periodic_events[i].correction_ms = 0;
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
            periodic_events[i].correction_ms = 0;
            periodic_events[i].count = 0;
            continue;
        }

    }

    if(next_minimal_period == UINT32_MAX)
        minimal_period = 0;

    period_counter = 0;
}
