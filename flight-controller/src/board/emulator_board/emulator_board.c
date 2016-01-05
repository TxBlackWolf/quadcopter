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

void board_showSystemClocks()
{
    // Empty.
}

bool board_initPeriodicTimer(TimerHandle_t *timer_handle __attribute__((unused)))
{
    // TODO: implement.
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
