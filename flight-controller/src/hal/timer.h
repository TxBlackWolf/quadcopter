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
#include <stdbool.h>

typedef uint32_t TimerDevice_t;
typedef uint8_t TimerChannel_t;

// Timer handle.
typedef struct {
    TimerDevice_t device;
    TimerChannel_t channel;
} TimerHandle_t;

// Timer config structure.
typedef struct {
    bool use_period;
    float period_ms;
    uint32_t frequency_hz;
} TimerConfig_t;

// General timer event callback.
typedef void (*TimerEventCallback_t)(void);

void timer_activate(TimerHandle_t *handle);
void timer_deactivate(TimerHandle_t *handle);

void timer_setEventFrequency(TimerHandle_t *handle, TimerConfig_t config);
bool timer_registerEventCallback(TimerHandle_t *handle, TimerEventCallback_t callback);
bool timer_unregisterEventCallback(TimerHandle_t *handle, TimerEventCallback_t callback);

uint32_t timer_getCounter(TimerHandle_t *handle);
void timer_setCounter(TimerHandle_t *handle, uint32_t value);

#endif
