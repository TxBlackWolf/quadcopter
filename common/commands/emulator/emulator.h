//=============================================================================================
//
// Filename   : emulator.h
// Author     : Kuba Sejdak
// Created on : 18.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef EMULATOR_H
#define EMULATOR_H

#include "common/commands/commands.h"

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    EMULATED_DEVICE_GPIO
} EmulatedDevice_t;

typedef struct {
    EmulatedDevice_t device;
} __attribute__((packed)) EmulatorCommand_t;

bool command_parseEmulator(uint8_t *payload, uint32_t size);

#endif
