////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       15.09.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "afro_esc_engine.h"
#include "board/board.h"
#include "board/board_pinout.h"
#include "board/console.h"
#include "hal/gpio.h"
#include "hal/pwm.h"

#define AFRO_ESC_MAX_PULSE_WIDTH_US         1860
#define AFRO_ESC_MIN_PULSE_WIDTH_US         1060
#define AFRO_ESC_MIN_PULSE_WIDTH_PERC       (((AFRO_ESC_MIN_PULSE_WIDTH_US * 100) / AFRO_ESC_MAX_PULSE_WIDTH_US) + 1)
#define AFRO_ESC_VALID_PULSE_WIDTH_DIFF     (100 - AFRO_ESC_MIN_PULSE_WIDTH_PERC)

static Engines_t engines;

//=============================================================================================
// HELPER FUNCTIONS
//=============================================================================================

static bool engines_initFrontLeft(GPIOConfig_t *gpio_config, PWMConfig_t *pwm_config)
{
    engines.front_left.gpio.port = ENGINE_FRONT_LEFT_PORT;
    engines.front_left.gpio.pin = ENGINE_FRONT_LEFT_PIN;
    engines.front_left.gpio.name = "front left engine";
    engines.front_left.timer.device = ENGINE_FRONT_LEFT_TIMER;
    engines.front_left.timer.channel = ENGINE_FRONT_LEFT_TIMER_CHANNEL;

    return board_engineInit(&engines.front_left, pwm_config, gpio_config);
}

static bool engines_initFrontRight(GPIOConfig_t *gpio_config, PWMConfig_t *pwm_config)
{
    engines.front_right.gpio.port = ENGINE_FRONT_RIGHT_PORT;
    engines.front_right.gpio.pin = ENGINE_FRONT_RIGHT_PIN;
    engines.front_right.gpio.name = "front right engine";
    engines.front_right.timer.device = ENGINE_FRONT_RIGHT_TIMER;
    engines.front_right.timer.channel = ENGINE_FRONT_RIGHT_TIMER_CHANNEL;

    return board_engineInit(&engines.front_right, pwm_config, gpio_config);
}

static bool engines_initRearLeft(GPIOConfig_t *gpio_config, PWMConfig_t *pwm_config)
{
    engines.rear_left.gpio.port = ENGINE_REAR_LEFT_PORT;
    engines.rear_left.gpio.pin = ENGINE_REAR_LEFT_PIN;
    engines.rear_left.gpio.name = "rear left engine";
    engines.rear_left.timer.device = ENGINE_REAR_LEFT_TIMER;
    engines.rear_left.timer.channel = ENGINE_REAR_LEFT_TIMER_CHANNEL;

    return board_engineInit(&engines.rear_left, pwm_config, gpio_config);
}

static bool engines_initReartRight(GPIOConfig_t *gpio_config, PWMConfig_t *pwm_config)
{
    engines.rear_right.gpio.port = ENGINE_REAR_RIGHT_PORT;
    engines.rear_right.gpio.pin = ENGINE_REAR_RIGHT_PIN;
    engines.rear_right.gpio.name = "rear right engine";
    engines.rear_right.timer.device = ENGINE_REAR_RIGHT_TIMER;
    engines.rear_right.timer.channel = ENGINE_REAR_RIGHT_TIMER_CHANNEL;

    return board_engineInit(&engines.rear_right, pwm_config, gpio_config);
}

//=============================================================================================
// INTERFACE FUNCTIONS
//=============================================================================================

bool engines_init()
{
    GPIOConfig_t gpio_config;
    gpio_config.direction = GPIO_DIRECTION_OUT;
    gpio_config.resistor_type = GPIO_RESISTOR_NONE;

    PWMConfig_t pwm_config;
    pwm_config.timer_config.use_period = true;
    pwm_config.timer_config.period_ms = AFRO_ESC_MAX_PULSE_WIDTH_US / 1000.0f;
    pwm_config.pulse_width_perc = 60;

    float engine_frequency = 1000.0f / pwm_config.timer_config.period_ms;
    console_write("engines: Afro ESC frequency: %d Hz\n", engine_frequency);
    console_write("engines: Afro ESC max pulse duration: %d us\n", AFRO_ESC_MAX_PULSE_WIDTH_US);
    console_write("engines: Afro ESC min pulse duration: %d us\n", AFRO_ESC_MIN_PULSE_WIDTH_US);
    console_write("engines: Afro ESC min pulse width: %d%%\n", AFRO_ESC_MIN_PULSE_WIDTH_PERC);

    if(!engines_initFrontLeft(&gpio_config, &pwm_config)) {
        console_write("engines: Failed to initialize %s\n", engines.front_left.gpio.name);
        return false;
    }

    if(!engines_initFrontRight(&gpio_config, &pwm_config)) {
        console_write("engines: Failed to initialize %s\n", engines.front_right.gpio.name);
        return false;
    }

    if(!engines_initRearLeft(&gpio_config, &pwm_config)) {
        console_write("engines: Failed to initialize %s\n", engines.rear_left.gpio.name);
        return false;
    }

    if(!engines_initReartRight(&gpio_config, &pwm_config)) {
        console_write("engines: Failed to initialize %s\n", engines.rear_right.gpio.name);
        return false;
    }

    return true;
}

Engines_t *engines_getHandle()
{
    return &engines;
}

void engines_enableOne(PWMHandle_t *engine)
{
    pwm_activate(engine);
    gpio_activate(&engine->gpio);
}

void engines_disableOne(PWMHandle_t *engine)
{
    gpio_deactivate(&engine->gpio);
    pwm_deactivate(engine);
}

void engines_enableAll()
{
    engines_enableOne(&engines.front_left);
    engines_enableOne(&engines.front_right);
    engines_enableOne(&engines.rear_left);
    engines_enableOne(&engines.rear_right);
}

void engines_disableAll()
{
    engines_disableOne(&engines.front_left);
    engines_disableOne(&engines.front_right);
    engines_disableOne(&engines.rear_left);
    engines_disableOne(&engines.rear_right);
}

void engines_setThrottle(PWMHandle_t *engine, uint32_t throttle_perc)
{
    float scalled_perc = throttle_perc / 100.0f;
    uint32_t scalled_throttle = AFRO_ESC_MIN_PULSE_WIDTH_PERC + scalled_perc * AFRO_ESC_VALID_PULSE_WIDTH_DIFF;

    pwm_setPulseWidthPerc(engine, scalled_throttle);
}
