//=============================================================================================
//
// Filename   : commands.c
// Author     : Kuba Sejdak
// Created on : 15.01.2016
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#include "commands.h"
#include "emulator.h"

#include <stdio.h>

static uint32_t command_nextId = 0;
static uint32_t command_receivedCount = 0;
static uint32_t command_lostCount = 0;
static uint32_t command_brokenCount = 0;

static CRCFunctor crc_functor = NULL;

bool command_checkVersion(CommandHeader_t *header)
{
    // TODO: implement.
    return true;
}

bool command_checkId(CommandHeader_t *header)
{
    uint32_t expectedId = command_nextId;
    command_nextId = header->command_id + 1;

    return (header->command_id == expectedId);
}

bool command_checkCRC(uint8_t *buffer, uint32_t size, uint32_t crc)
{
    // TODO: implement.
    return true;
}

CommandParsingError_t command_parse(uint8_t *buffer)
{
    CommandHeader_t *header = (CommandHeader_t *) buffer;
    ++command_receivedCount;

    if(!command_checkVersion(header)) {
        ++command_brokenCount;
        return PARSING_BAD_VERSION;
    }

    if(!command_checkId(header))
        ++command_lostCount;

    if(!command_checkCRC(buffer + sizeof(CommandHeader_t), header->payload_size, header->payload_crc)) {
        ++command_brokenCount;
        return PARSING_BAD_CRC;
    }

    bool parsing_stat = false;
    switch(header->type) {
    case COMMAND_EMULATOR:
        parsing_stat = command_parseEmulator(buffer + sizeof(CommandHeader_t), header->payload_size);
        break;
    case COMMAND_CONTROL:
        ++command_brokenCount;
        return PARSING_UNSUPPORTED_TYPE;
    case COMMAND_TELEMETRY:
        ++command_brokenCount;
        return PARSING_UNSUPPORTED_TYPE;
    case COMMAND_SYS_STATUS:
        ++command_brokenCount;
        return PARSING_UNSUPPORTED_TYPE;
    case COMMAND_DEBUG:
        ++command_brokenCount;
        return PARSING_UNSUPPORTED_TYPE;
    default:
        ++command_brokenCount;
        return PARSING_UNSUPPORTED_TYPE;
    }

    if(!parsing_stat) {
        ++command_brokenCount;
        return PARSING_INVALID_DATA;
    }

    return PARSING_OK;
}
