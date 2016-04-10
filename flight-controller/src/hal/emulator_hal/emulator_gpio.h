//=============================================================================================
//
// Filename   : network_uart.h
// Author     : Kuba Sejdak
// Created on : 09.04.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef EMULATOR_GPIO_H
#define EMULATOR_GPIO_H

#include "hal/gpio.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool enabled;
} EmulatorGPIOPrivateData_t;

bool emulator_gpioInit(GPIOHandle_t *handle);

#endif
