//---------------------------------------------------------------------------------------------------------------
//
// Filename   : linux_timer.c
// Author     : Kuba Sejdak
// Created on : 04.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "linux_timer.h"

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//---------------------------------------------------------------------------------------------------------------
// INTERFACE FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

bool emulator_timerInit(TimerHandle_t *handle, Emulator_TimerConfig_t *config)
{
    struct sigevent sig_event;
    sig_event.sigev_notify = SIGEV_SIGNAL;
    sig_event.sigev_signo = config->sig_num;
    sig_event.sigev_value.sival_ptr = handle;

    struct sigaction sig_action;
    sig_action.sa_flags = SA_SIGINFO;
    sigemptyset(&sig_action.sa_mask);
    sig_action.sa_sigaction = config->signal_handler;

    if(sigaction(sig_event.sigev_signo, &sig_action, NULL)) {
        console_write("Failed to register signal handler for periodic timer: %s.", strerror(errno));
        return false;
    }

    timer_t timer_id;
    if(timer_create(CLOCK_REALTIME, &sig_event, &timer_id)) {
        console_write("Failed to create periodic timer: %s.", strerror(errno));
        return false;
    }

    // Use private field as enable flag for timer.
    handle->private_data = 0;

    struct itimerspec itimer_spec;
    itimer_spec.it_value.tv_sec = config->period_ms / 1000;
    itimer_spec.it_value.tv_nsec = (config->period_ms * 1000000) % 1000000000;
    itimer_spec.it_interval.tv_sec = itimer_spec.it_value.tv_sec;
    itimer_spec.it_interval.tv_nsec = itimer_spec.it_value.tv_nsec;

    if(timer_settime(timer_id, CLOCK_REALTIME, &itimer_spec, NULL)) {
        console_write("Failed to set periodic timer: %s.", strerror(errno));
        return false;
    }

    handle->device = *((TimerDevice_t *) timer_id);
    return true;
}

void timer_activate(TimerHandle_t *handle)
{
    handle->private_data = 1;
}

void timer_deactivate(TimerHandle_t *handle)
{
    handle->private_data = 0;
}

uint32_t timer_getCounter(TimerHandle_t *handle __attribute__((unused)))
{
    // Empty.
    return 0;
}

void timer_setCounter(TimerHandle_t *handle __attribute__((unused)), uint32_t value __attribute__((unused)))
{
    // Empty.
}
