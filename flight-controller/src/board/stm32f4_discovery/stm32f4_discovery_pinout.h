//---------------------------------------------------------------------------------------------------------------
//
// Filename   : stm32f4_discovery_pinout.h
// Author     : Kuba Sejdak
// Created on : 21.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef STM32F4_DISCOVERY_PINOUT_H
#define STM32F4_DISCOVERY_PINOUT_H

#include "board/board_drivers_support.h"

#if ACCELEROMETER_ENABLED
// TODO: implement
#endif

#if BAROMETER_ENABLED
// TODO: implement
#endif

#if BUZZER_ENABLED
// TODO: implement
#endif

#if CAMERA_ENABLED
// TODO: implement
#endif

#if ENGINES_ENABLED
// TODO: implement
#endif

#if GYROSCOPE_ENABLED
// TODO: implement
#endif

#if LIGHTS_ENABLED
    #define STROBE_PORT     1
    #define STROBE_PIN      10
#endif

#if MAGNETOMETER_ENABLED
// TODO: implement
#endif

#endif
