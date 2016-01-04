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

#include "board/board.h"
#include "board/clock.h"

void board_showSystemClocks()
{
}

bool board_initPeriodicTimer(TimerHandle_t *timer_handle)
{
    return true;
}

bool board_strobeInit(GPIOHandle_t *gpio_handle, GPIOConfig_t gpio_general_config)
{
    return true;
}

bool board_engineInit(PWMHandle_t *pwm_handle, PWMConfig_t pwm_config, GPIOConfig_t gpio_general_config)
{
    return true;
}
