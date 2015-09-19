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

#include "timer.h"
#include "gpio.h"

#include <stdint.h>

// PWM handle.
typedef struct
{
    TimerHandle_t timer;
    GPIOHandle_t gpio;
} PWMHandle_t;

// PWM config structure.
typedef struct
{
    uint32_t frequency_hz;
    uint32_t pulse_width_perc;
    uint32_t channel;
    GPIOConfig_t gpio_config;
} PWMConfig_t;

void pwm_activate(TimerDevice_t device);
void pwm_deactivate(TimerDevice_t device);

void pwm_setFrequency(uint32_t frequency_hz, TimerDevice_t device);
void pwm_setPulseWidthPerc(uint32_t width_perc, TimerDevice_t device);
void pwm_setPulseWidthUsec(uint32_t width_us, TimerDevice_t device);

#endif
