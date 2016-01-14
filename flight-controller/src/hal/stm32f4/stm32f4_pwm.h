//=============================================================================================
//
// Filename   : stm32f4_pwm.h
// Author     : Kuba Sejdak
// Created on : 14.09.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef STM32F4_PWM_H
#define STM32F4_PWM_H

#include "hal/pwm.h"
#include "stm32f4_timer.h"

bool stm32f4_pwmInit(PWMHandle_t *handle, PWMConfig_t config);

#endif
