////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       04.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "linux_timer.h"
#include "board/console.h"

#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//=============================================================================================
// INTERFACE FUNCTIONS
//=============================================================================================

bool emulator_timerInit(TimerHandle_t *handle, Emulator_TimerConfig_t *config)
{
    // Register handler for given signal.
    struct sigevent sig_event;
    sig_event.sigev_notify = SIGEV_SIGNAL;
    sig_event.sigev_signo = config->sig_num;
    sig_event.sigev_value.sival_ptr = handle;

    struct sigaction sig_action;
    sig_action.sa_flags = SA_SIGINFO;
    sigemptyset(&sig_action.sa_mask);
    sig_action.sa_sigaction = config->signal_handler;

    if(sigaction(sig_event.sigev_signo, &sig_action, NULL)) {
        console_write("linux_timer: Failed to register signal handler for Linux timer: %s.\n", strerror(errno));
        return false;
    }

    // Create Linux timer.
    timer_t timer_id;
    if(timer_create(CLOCK_REALTIME, &sig_event, &timer_id)) {
        console_write("linux_timer: Failed to create Linux timer: %s.\n", strerror(errno));
        return false;
    }

    struct itimerspec itimer_spec;
    itimer_spec.it_value.tv_sec = config->period_ms / 1000;
    itimer_spec.it_value.tv_nsec = (config->period_ms * 1000000) % 1000000000;
    itimer_spec.it_interval.tv_sec = itimer_spec.it_value.tv_sec;
    itimer_spec.it_interval.tv_nsec = itimer_spec.it_value.tv_nsec;

    if(timer_settime(timer_id, CLOCK_REALTIME, &itimer_spec, NULL)) {
        console_write("linux_timer: Failed to set Linux timer: %s.\n", strerror(errno));
        return false;
    }

    // Allocate and init private data.
    Emulator_TimerPrivateData_t *private_data = (Emulator_TimerPrivateData_t *) malloc(sizeof(Emulator_TimerPrivateData_t));
    if(!private_data) {
        console_write("linux_timer: Failed to alloc Linux timer private data: %s.\n", strerror(errno));
        return false;
    }

    private_data->enabled = false;
    private_data->callback = NULL;

    handle->device = *((TimerDevice_t *) timer_id);
    handle->private_data = private_data;
    return true;
}

void timer_activate(TimerHandle_t *handle)
{
    Emulator_TimerPrivateData_t *private_data = (Emulator_TimerPrivateData_t *) handle->private_data;
    assert(private_data);
    private_data->enabled = true;
}

void timer_deactivate(TimerHandle_t *handle)
{
    Emulator_TimerPrivateData_t *private_data = (Emulator_TimerPrivateData_t *) handle->private_data;
    assert(private_data);
    private_data->enabled = false;
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
