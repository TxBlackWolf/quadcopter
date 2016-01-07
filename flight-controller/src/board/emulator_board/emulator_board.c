//---------------------------------------------------------------------------------------------------------------
//
// Filename   : emulator_board.c
// Author     : Kuba Sejdak
// Created on : 04.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "emulator_board.h"
#include "signal_handlers.h"
#include "board/clock.h"
#include "board/console.h"

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void board_showSystemClocks()
{
    // Empty.
}

bool board_initPeriodicTimer(TimerHandle_t *timer_handle)
{
    struct sigevent sig_event;
    sig_event.sigev_notify = SIGEV_SIGNAL;
    sig_event.sigev_signo = SIGALRM;

	if(signal(SIGALRM, signal_handler) == SIG_ERR) {
		console_write("Failed to register signal handler for periodic timer: %s.", strerror(errno));
		return false;
	}

	timer_t timer_id;
	if(timer_create(CLOCK_REALTIME, &sig_event, &timer_id)) {
        console_write("Failed to create periodic timer: %s.", strerror(errno));
        return false;
    }

	struct itimerspec itimer_spec;
    itimer_spec.it_value.tv_sec = CLOCK_PERIODIC_TIMER_PERIOD_MS / 1000;
    itimer_spec.it_value.tv_nsec = (CLOCK_PERIODIC_TIMER_PERIOD_MS * 1000000) % 1000000000;
    itimer_spec.it_interval.tv_sec = itimer_spec.it_value.tv_sec;
    itimer_spec.it_interval.tv_nsec = itimer_spec.it_value.tv_nsec;

	if(timer_settime(timer_id, CLOCK_REALTIME, &itimer_spec, NULL)) {
        console_write("Failed to set periodic timer: %s.", strerror(errno));
        return false;
    }

	timer_handle->device = *((TimerDevice_t *) timer_id);
    return true;
}

bool board_strobeInit(GPIOHandle_t *gpio_handle __attribute__((unused)), GPIOConfig_t gpio_general_config __attribute__((unused)))
{
    // TODO: implement.
    return true;
}

bool board_engineInit(PWMHandle_t *pwm_handle __attribute__((unused)), PWMConfig_t pwm_config __attribute__((unused)), GPIOConfig_t gpio_general_config __attribute__((unused)))
{
    // TODO: implement.
    return true;
}
