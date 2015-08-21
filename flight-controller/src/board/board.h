//---------------------------------------------------------------------------------------------------------------
//
// Filename   : platform.h
// Author     : Kuba Sejdak
// Created on : 23.07.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef PLATFORM_H
#define PLATFORM_H

#include "hal/gpio.h"

#include <stdbool.h>

bool board_init();

void board_strobeInit(GPIOConfig_t *config);

#endif
