////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       05.09.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TIMER_H
#define TIMER_H

#include "gpio.h"

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t TimerDevice_t;     ///< Timer device id.
typedef uint8_t TimerChannel_t;     ///< Timer channel id.

/// @brief Timer config structure.
typedef struct {
    bool use_period;                ///< Flag indicating which union field should be used.
    union {
        float period_ms;            ///< Timer period in miliseconds.
        uint32_t frequency_hz;      ///< Timer frequency in Hertzs.
    };
} TimerConfig_t;

/// @brief Timer device handle.
typedef struct {
    TimerDevice_t device;           ///< Timer device id.
    TimerChannel_t channel;         ///< Timer channel id.
    void *private_data;             ///< Pointer to driver private data.
} TimerHandle_t;

/// @brief Activates timer device.
/// @param [in] handle          Timer device to be activated.
void timer_activate(TimerHandle_t *handle);

/// @brief Deactivates timer device.
/// @param [in] handle          Timer device to be deactivated.
void timer_deactivate(TimerHandle_t *handle);

/// @brief Returns actual counter value in device register.
/// @param [in] handle          Timer device to be checked.
/// @return Counter value.
uint32_t timer_getCounter(TimerHandle_t *handle);

/// @brief Sets new counter value in device register.
/// @param [in] handle          Timer device to be modified.
/// @param [in] value           New counter value.
void timer_setCounter(TimerHandle_t *handle, uint32_t value);

#endif
