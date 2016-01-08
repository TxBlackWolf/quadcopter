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
#include "hal/emulator_hal/linux_timer.h"

#include <signal.h>

void board_showSystemClocks()
{
    // Empty.
}

bool board_initPeriodicTimer(TimerHandle_t *timer_handle)
{
    Emulator_TimerConfig_t timer_config;
    timer_config.signal_handler = sigalrm_handler;
    timer_config.sig_num = SIGALRM;
    timer_config.period_ms = CLOCK_PERIODIC_TIMER_PERIOD_MS;

    if(!emulator_timerInit(timer_handle, &timer_config)) {
        console_write("board: Failed to initialize emulator timer for periodic timer\n");
        return false;
    }

    timer_activate(timer_handle);
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
