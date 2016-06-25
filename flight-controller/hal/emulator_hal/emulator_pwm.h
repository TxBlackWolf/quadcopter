////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       15.05.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef EMULATOR_PWM_H
#define EMULATOR_PWM_H

#include "hal/pwm.h"

#include <stdbool.h>

typedef struct {
    bool enabled;
} EmulatorPWMPrivateData_t;

bool emulator_pwmInit(PWMHandle_t *handle);

#endif
