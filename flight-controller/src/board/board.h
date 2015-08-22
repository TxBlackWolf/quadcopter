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

bool board_init();

GPIOHandle_t board_strobeInit(GPIOPort_t port, GPIOPort_t pin, GPIOConfig_t config);

#endif
