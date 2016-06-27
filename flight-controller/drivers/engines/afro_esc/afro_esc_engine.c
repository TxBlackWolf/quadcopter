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
#include "core/controller/system_status.h"
#include "hal/gpio.h"
#include "hal/pwm.h"

#include <stdio.h>

#define AFRO_ESC_ENGINES_NAME               "Afro ESC engines"

#define AFRO_ESC_MAX_PULSE_WIDTH_US         1860                                                                        ///< Maximal pulse width in ms for engine ESC.
#define AFRO_ESC_MIN_PULSE_WIDTH_US         1060                                                                        ///< Minimal pulse width in ms for engine ESC.
#define AFRO_ESC_MIN_PULSE_WIDTH_PERC       (((AFRO_ESC_MIN_PULSE_WIDTH_US * 100) / AFRO_ESC_MAX_PULSE_WIDTH_US) + 1)   ///< Minimal percentage of PWM for this configuration.
#define AFRO_ESC_VALID_PULSE_WIDTH_DIFF     (100 - AFRO_ESC_MIN_PULSE_WIDTH_PERC)                                       ///< Difference between 100% and minimal percentage.

static Engine_t engines[ENGINE_COUNT];

//=============================================================================================
// HELPER FUNCTIONS
//=============================================================================================

/// @brief Initializes one engine with given configuration.
/// @param [in] id              Engine id.
/// @param [in] pwm_config      PWM configuration.
/// @note This uses GCC's statement expressions, thus it is not portable.
#define engines_initOne(id, pwm_config)                                 \
    ({                                                                  \
        Engine_t *engine = &engines[id];                                \
        PWMHandle_t *handle = &engine->handle;                          \
        handle->gpio.port = GET_ENGINE_PORT(id);                        \
        handle->gpio.pin = GET_ENGINE_PIN(id);                          \
        handle->gpio.name = GET_ENGINE_NAME(id);                        \
        handle->timer.device = GET_ENGINE_TIMER(id);                    \
        handle->timer.channel = GET_ENGINE_TIMER_CHANNEL(id);           \
        engine->initialized = board_engineInit(handle, pwm_config);     \
        engine->initialized;                                            \
    })

//=============================================================================================
// INTERFACE FUNCTIONS
//=============================================================================================

bool engines_init()
{
    PWMConfig_t pwm_config;
    pwm_config.gpio_config.direction = GPIO_DIRECTION_OUT;
    pwm_config.gpio_config.resistor_type = GPIO_RESISTOR_NONE;
    pwm_config.timer_config.use_period = true;
    pwm_config.timer_config.period_ms = AFRO_ESC_MAX_PULSE_WIDTH_US / 1000.0f;
    pwm_config.pulse_width_perc = 60;

    float engine_frequency = 1000.0f / pwm_config.timer_config.period_ms;
    console_write("engines: Afro ESC frequency: %d Hz\n", engine_frequency);
    console_write("engines: Afro ESC max pulse duration: %d us\n", AFRO_ESC_MAX_PULSE_WIDTH_US);
    console_write("engines: Afro ESC min pulse duration: %d us\n", AFRO_ESC_MIN_PULSE_WIDTH_US);
    console_write("engines: Afro ESC min pulse width: %d%%\n", AFRO_ESC_MIN_PULSE_WIDTH_PERC);

    if (!engines_initOne(ENGINE_FRONT_LEFT, &pwm_config)) {
        console_write("engines: Failed to initialize %s\n", GET_ENGINE_NAME(ENGINE_FRONT_LEFT));
        return false;
    }

    if (!engines_initOne(ENGINE_FRONT_RIGHT, &pwm_config)) {
        console_write("engines: Failed to initialize %s\n", GET_ENGINE_NAME(ENGINE_FRONT_RIGHT));
        return false;
    }

    if (!engines_initOne(ENGINE_REAR_LEFT, &pwm_config)) {
        console_write("engines: Failed to initialize %s\n", GET_ENGINE_NAME(ENGINE_REAR_LEFT));
        return false;
    }

    if (!engines_initOne(ENGINE_REAR_RIGHT, &pwm_config)) {
        console_write("engines: Failed to initialize %s\n", GET_ENGINE_NAME(ENGINE_REAR_RIGHT));
        return false;
    }

    systemStatus_setEnginesName(AFRO_ESC_ENGINES_NAME);
    return true;
}

void engines_enableOne(EngineId_t id)
{
    if (!engines[id].initialized)
        return;

    pwm_activate(&engines[id].handle);
    gpio_activate(&engines[id].handle.gpio);
}

void engines_disableOne(EngineId_t id)
{
    if (!engines[id].initialized)
        return;

    gpio_deactivate(&engines[id].handle.gpio);
    pwm_deactivate(&engines[id].handle);
}

void engines_enableAll()
{
    for (int i = ENGINE_FRONT_LEFT; i < ENGINE_COUNT; ++i)
        engines_enableOne(i);
}

void engines_disableAll()
{
    for (int i = ENGINE_FRONT_LEFT; i < ENGINE_COUNT; ++i)
        engines_disableOne(i);
}

void engines_setThrottle(EngineId_t id, uint32_t throttle_perc)
{
    if (!engines[id].initialized)
        return;

    float scalled_perc = throttle_perc / 100.0f;
    uint32_t scalled_throttle = AFRO_ESC_MIN_PULSE_WIDTH_PERC + scalled_perc * AFRO_ESC_VALID_PULSE_WIDTH_DIFF;

    pwm_setPulseWidthPerc(&engines[id].handle, scalled_throttle);
}
