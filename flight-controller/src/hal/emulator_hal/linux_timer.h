//=============================================================================================
//
// Filename   : linux_timer.h
// Author     : Kuba Sejdak
// Created on : 04.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef LINUX_TIMER_H
#define LINUX_TIMER_H

#include "hal/timer.h"

#include <signal.h>
#include <stdbool.h>
#include <stdint.h>

typedef void (*signal_handler_t)(int, siginfo_t *, void *);
typedef void (*timer_callback_t)();

// Timer config structure.
typedef struct {
    signal_handler_t signal_handler;
    int sig_num;
    uint32_t period_ms;
} Emulator_TimerConfig_t;

typedef struct {
    bool enabled;
    timer_callback_t callback;
} LinuxTimerPrivateData_t;

bool emulator_timerInit(TimerHandle_t *handle, Emulator_TimerConfig_t *config);

#endif
