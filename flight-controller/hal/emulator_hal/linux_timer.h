////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       04.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef LINUX_TIMER_H
#define LINUX_TIMER_H

#include "hal/hal.h"
#include "hal/timer.h"

#include <signal.h>
#include <stdbool.h>
#include <stdint.h>

typedef void (*signal_handler_t)(int, siginfo_t *, void *);

// Timer config structure.
typedef struct {
    signal_handler_t signal_handler;
    int sig_num;
    uint32_t period_ms;
} Emulator_TimerConfig_t;

typedef struct {
    bool enabled;
    HALEventCallback_t callback;
} Emulator_TimerPrivateData_t;

bool emulator_timerInit(TimerHandle_t *handle, Emulator_TimerConfig_t *config);

#endif
