//---------------------------------------------------------------------------------------------------------------
//
// Filename   : pwm.h
// Author     : Kuba Sejdak
// Created on : 14.09.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef PWM_H
#define PWM_H

#include "gpio.h"
#include "timer.h"

#include <stdint.h>

// PWM handle.
typedef struct {
    TimerHandle_t timer;
    GPIOHandle_t gpio;
    uint16_t period;
} PWMHandle_t;

// PWM config structure.
typedef struct {
    TimerConfig_t timer_config;
    uint32_t pulse_width_perc;
} PWMConfig_t;

void pwm_activate(PWMHandle_t *handle);
void pwm_deactivate(PWMHandle_t *handle);

void pwm_setPulseWidthPerc(PWMHandle_t *handle, uint32_t width_perc);

#endif
