//---------------------------------------------------------------------------------------------------------------
//
// Filename   : signal_handlers.c
// Author     : Kuba Sejdak
// Created on : 06.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "signal_handlers.h"
#include "board/clock.h"
#include "hal/timer.h"

#include <assert.h>

void sigalrm_handler(int sig_num, siginfo_t *sig_info, void *unused __attribute__((unused)))
{
    assert(sig_num == SIGALRM);

    TimerHandle_t *timer_handle = (TimerHandle_t *) sig_info->si_value.sival_ptr;
    if(timer_handle->private_data == 1)
        clock_processPeriodicEvents();
}
