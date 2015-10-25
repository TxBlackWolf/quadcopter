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

#define AFRO_ESC_PWM_FREQUENCY_HZ           537
#define AFRO_ESC_MAX_PULSE_WIDTH_US         1860
#define AFRO_ESC_MIN_PULSE_WIDTH_US         1060
#define AFRO_ESC_MIN_PULSE_WIDTH_PERC       (((AFRO_ESC_MIN_PULSE_WIDTH_US * 100) / AFRO_ESC_MAX_PULSE_WIDTH_US) + 1)
#define AFRO_ESC_VALID_PULSE_WIDTH_DIFF     (100 - AFRO_ESC_MIN_PULSE_WIDTH_PERC)

PWMHandle_t front_left_engine;
PWMHandle_t front_right_engine;
PWMHandle_t rear_left_engine;
PWMHandle_t rear_right_engine;

bool engines_init()
{
    GPIOConfig_t gpio_config;
    gpio_config.direction = GPIO_DIRECTION_OUT;
    gpio_config.resistor_type = GPIO_RESISTOR_NONE;

    front_left_engine.gpio.port = ENGINE_FRONT_LEFT_PORT;
    front_left_engine.gpio.pin = ENGINE_FRONT_LEFT_PIN;
    front_left_engine.gpio.name = "front left engine";
    front_left_engine.timer.device = ENGINE_FRONT_LEFT_TIMER;
    front_left_engine.timer.channel = ENGINE_FRONT_LEFT_TIMER_CHANNEL;

    PWMConfig_t pwm_config;
    pwm_config.frequency_hz = AFRO_ESC_PWM_FREQUENCY_HZ;
    pwm_config.pulse_width_perc = 0;

    console_write("engines: Afro ESC frequency: %d Hz\n", AFRO_ESC_PWM_FREQUENCY_HZ);
    console_write("engines: Afro ESC max pulse duration: %d us\n", AFRO_ESC_MAX_PULSE_WIDTH_US);
    console_write("engines: Afro ESC min pulse duration: %d us\n", AFRO_ESC_MIN_PULSE_WIDTH_US);
    console_write("engines: Afro ESC min pulse width: %d%%\n", AFRO_ESC_MIN_PULSE_WIDTH_PERC);

    return board_engineInit(&front_left_engine, pwm_config, gpio_config);
}

void engines_setThrottle(PWMHandle_t *engine, uint32_t throttle_perc)
{
    float scalled_perc = throttle_perc / 100.0f;
    uint32_t scalled_throttle = AFRO_ESC_MIN_PULSE_WIDTH_PERC + scalled_perc * AFRO_ESC_VALID_PULSE_WIDTH_DIFF;

    pwm_setPulseWidthPerc(engine, scalled_throttle);
}
