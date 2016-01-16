//=============================================================================================
//
// Filename   : Command.h
// Author     : Kuba Sejdak
// Created on : 15.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef COMMAND_H
#define COMMAND_H

#include <stdint.h>

#define COMMANDS_VERSION                "0.0.1"
#define COMMANDS_PAYLOAD_MAX_SIZE       1024

typedef enum {
    COMMAND_EMULATOR,
    COMMAND_CONTROL,
    COMMAND_TELEMETRY
} CommandType_t;

typedef struct {
    const char *version;
    CommandType_t type;
    uint8_t payload_size;
    uint8_t payload[COMMANDS_PAYLOAD_MAX_SIZE];
} Command_t;

#endif
