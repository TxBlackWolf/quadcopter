////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       14.09.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PWM_H
#define PWM_H

#include "gpio.h"
#include "timer.h"

#include <stdint.h>

/// @brief PWM device handle.
typedef struct {
    TimerHandle_t timer;            ///< Timer device handle used for PWM.
    GPIOHandle_t gpio;              ///< GPIO device handle used for PWM.
    uint16_t period;                ///< Current PWM period.
} PWMHandle_t;

/// @brief PWM config structure.
typedef struct {
    TimerConfig_t timer_config;     ///< Desired timer configuration.
    GPIOConfig_t gpio_config;       ///< Desired gpio configuration.
    uint32_t pulse_width_perc;      ///< Desired initial percentage of pulse width.
} PWMConfig_t;

/// @brief Activates PWM device.
/// @param [in] handle          PWM device to be activated.
void pwm_activate(PWMHandle_t *handle);

/// @brief Deactivates PWM device.
/// @param [in] handle          PWM device to be deactivated.
void pwm_deactivate(PWMHandle_t *handle);

/// @brief Sets current percentage of PWM width.
/// @param [in] handle          PWM device to be manipulated.
/// @param [in] width_perc      Desired PWM width percentage.
void pwm_setPulseWidthPerc(PWMHandle_t *handle, uint32_t width_perc);

#endif
