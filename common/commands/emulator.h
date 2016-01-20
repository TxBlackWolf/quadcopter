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

#include "commands.h"

#include <stdbool.h>
#include <stdint.h>

typedef void (*CommandCallback_t)(uint8_t *, uint32_t);

typedef enum {
    EMULATED_DEVICE_GPIO,
	EMULATED_DEVICE_COUNT
} EmulatedDevice_t;

typedef struct {
    EmulatedDevice_t device;
} __attribute__((packed)) EmulatorCommand_t;

typedef struct {
	uint32_t port;
	uint32_t pin;
	uint32_t value;
	uint32_t name_size;
} __attribute__((packed)) EmulatorCommandGPIO_t;

bool command_registerEmulatorCallback(EmulatedDevice_t device, CommandCallback_t callback);
bool command_unregisterEmulatorCallback(EmulatedDevice_t device);
bool command_parseEmulator(uint8_t *payload, uint32_t size);

#endif
