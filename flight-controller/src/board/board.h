//---------------------------------------------------------------------------------------------------------------
//
// Filename   : board.h
// Author     : Kuba Sejdak
// Created on : 23.07.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef BOARD_H
#define BOARD_H

#include "hal/gpio.h"

#include <stdbool.h>

void panic(const char *format, ...);

bool board_init();

bool board_strobeInit(GPIOHandle_t gpio_handle, GPIOConfig_t config);

#endif
