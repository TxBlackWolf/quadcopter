////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       15.09.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ENGINE_H
#define ENGINE_H

#include "hal/pwm.h"

#include <stdbool.h>

/// @brief Engine id enumeration.
typedef enum {
    ENGINE_FRONT_LEFT,          ///< Front left engine id.
    ENGINE_FRONT_RIGHT,         ///< Front right engine id.
    ENGINE_REAR_LEFT,           ///< Rear left engine id.
    ENGINE_REAR_RIGHT,          ///< Rear right engine id.
    ENGINE_COUNT                ///< Number of engines. SHOULD BE LAST.
} EngineId_t;

/// @brief Initializes engines.
/// @return True on success, false otherwise.
bool engines_init();

/// @brief Enabled one engine with given id.
/// @param [in] engine          Id of engine to be enabled.
void engines_enableOne(EngineId_t engine);

/// @brief Disabled one engine with given id.
/// @param [in] engine          Id of engine to be disabled.
void engines_disableOne(EngineId_t engine);

/// @brief Enables all engines.
void engines_enableAll();

/// @brief Disables all engines.
void engines_disableAll();

/// @brief Sets throttle percentage of give engine.
/// @param [in] engine          Id of engine to manipulate.
/// @param [in] throttle_perc   New throttle percentage (values from range 0-100 %).
void engines_setThrottle(EngineId_t engine, uint32_t throttle_perc);

#endif
