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

#include <stdbool.h>
#include <stdint.h>

#define COMMANDS_VERSION            "0.0.1"
#define COMMANDS_MAX_SIZE_BYTES     1024

typedef enum {
    PARSING_OK,
    PARSING_BAD_VERSION,
    PARSING_PACKET_LOST,
    PARSING_BAD_CRC,
    PARSING_UNSUPPORTED_TYPE,
    PARSING_INVALID_DATA
} CommandParsingError_t;

typedef enum {
    COMMAND_EMULATOR,               // Commands related to emulator (ex. GPIO status, PWM wave width).
    COMMAND_CONTROL,                // Commands sent by GroundStation or RC system to control flight (speed, pitch, yaw, etc...).
    COMMAND_TELEMETRY,              // All messages, that hold some telemetry data.
    COMMAND_SYS_STATUS,             // System status messages.
    COMMAND_DEBUG                   // Debug messages. Should be disabled in release firmware.
} CommandType_t;

typedef struct {
    uint16_t version_major;
    uint16_t version_minor;
    uint16_t version_patch;
    uint32_t command_id;
    CommandType_t type;
    uint8_t payload_size;
    uint32_t payload_crc;
} __attribute__((packed)) CommandHeader_t;

typedef uint32_t (*CRCFunctor)(uint8_t *, uint32_t);

void command_registerCRCFunctor(CRCFunctor functor);

bool command_checkVersion(CommandHeader_t *header);
bool command_checkId(CommandHeader_t *header);
bool command_checkCRC(uint8_t *buffer, uint32_t size, uint32_t crc);
CommandParsingError_t command_parse(uint8_t *buffer);

#endif
