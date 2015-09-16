//---------------------------------------------------------------------------------------------------------------
//
// Filename   : afro_esc_engine.c
// Author     : Kuba Sejdak
// Created on : 15.09.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "afro_esc_engine.h"
#include "drivers/engines/engine.h"
#include "hal/gpio.h"
#include "hal/pwm.h"
#include "board/board.h"
#include "board/board_pinout.h"
#include "board/console.h"

#define AFRO_ESC_PWM_FREQUENCY_HZ   10000

static PWMHandle_t front_left_engine_handle;
static PWMHandle_t front_right_engine_handle;
static PWMHandle_t rear_left_engine_handle;
static PWMHandle_t rear_right_engine_handle;

bool engines_init()
{
    GPIOConfig_t gpio_config;
    gpio_config.direction = GPIO_DIRECTION_OUT;
    gpio_config.resistor_type = GPIO_RESISTOR_NONE;

    front_left_engine_handle.gpio_handle.port = ENGINE_FRONT_LEFT_PORT;
    front_left_engine_handle.gpio_handle.pin = ENGINE_FRONT_LEFT_PIN;

    PWMConfig_t pwm_config;
    pwm_config.frequency_hz = AFRO_ESC_PWM_FREQUENCY_HZ;
    pwm_config.pulse_width_perc = 0;
    pwm_config.gpio_config = gpio_config;

    return board_engineInit(front_left_engine_handle, pwm_config)
}
