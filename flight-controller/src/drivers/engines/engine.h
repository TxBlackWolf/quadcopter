//---------------------------------------------------------------------------------------------------------------
//
// Filename   : engine.h
// Author     : Kuba Sejdak
// Created on : 15.09.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef ENGINE_H
#define ENGINE_H

#include "hal/pwm.h"

#include <stdbool.h>

extern PWMHandle_t front_left_engine;
extern PWMHandle_t front_right_engine;
extern PWMHandle_t rear_left_engine;
extern PWMHandle_t rear_right_engine;

bool engines_init();
void engines_enable_one(PWMHandle_t *engine);
void engines_disable_one(PWMHandle_t *engine);
void engines_enable_all();
void engines_disable_all();

void engines_setThrottle(PWMHandle_t *engine, uint32_t throttle_perc);

#endif
