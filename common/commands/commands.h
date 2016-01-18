//=============================================================================================
//
// Filename   : commands.h
// Author     : Kuba Sejdak
// Created on : 15.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

#define COMMANDS_VERSION            "0.0.1"

typedef enum {
    COMMAND_EMULATOR,               // Commands related to emulator (ex. GPIO status, PWM wave width).
    COMMAND_CONTROL,                // Commands sent by GroundStation or RC system to control flight (speed, pitch, yaw, etc...).
    COMMAND_TELEMETRY,              // All messages, that hold some telemetry data.
    COMMAND_SYS_STATUS,             // System status messages.
    COMMAND_DEBUG                   // Debug messages. Should be disabled in release firmware.
} CommandType_t;

typedef struct {
    uint8_t version_major;
    uint8_t version_minor;
    uint8_t version_patch;
    CommandType_t type;
    uint8_t payload_size;
    uint32_t command_id;
    uint32_t crc;
} __attribute__((packed)) CommandHeader_t;

#endif
