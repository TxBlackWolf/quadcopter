////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       24.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
//////////////////////////////////////////////////////////////////////////////////////////////// 

#include "command_encoder.h"
#include "command_common.h"

static uint32_t commandEncoder_nextId = 0;

/// @brief Initializes common command header in given buffer.
/// @param [in/out] buffer          Buffer for command.
/// @return Size of created data.
static int commandEncoder_initHeader(uint8_t *buffer, CommandType_t type)
{
    /// @todo Add automatic version deserialization from string.
    CommandHeader_t *header = (CommandHeader_t *) buffer;
    header->sync1 = COMMAND_SYNC_BYTE_1;
    header->sync2 = COMMAND_SYNC_BYTE_2;
    header->sync3 = COMMAND_SYNC_BYTE_3;
    header->version_major = 0;
    header->version_minor = 0;
    header->version_patch = 1;
    header->command_id = commandEncoder_nextId++;
    header->type = type;
    header->payload_size = 0;
    header->payload_crc = 0;

    return sizeof(CommandHeader_t);
}

/// @brief Fills size of payload and computer CRC.
/// @param [in/out] buffer          Buffer for command.
/// @return Size of created data.
static void commandEncoder_finish(uint8_t *buffer, int size)
{
    CommandHeader_t *header = (CommandHeader_t *) buffer;
    header->payload_size = size - sizeof(CommandHeader_t);
    header->payload_crc = command_computeCRC(buffer + sizeof(CommandHeader_t), header->payload_size);
}

int commandEncoder_createEmulatorCommand(uint8_t *buffer, EmulatedDevice_t device, void *command)
{
    int idx = commandEncoder_initHeader(buffer, COMMAND_EMULATOR);
    
    EmulatorHeader_t *emulator_header = (EmulatorHeader_t *) &buffer[idx];
    emulator_header->device = device;
    idx += sizeof(EmulatorHeader_t);

    switch(device) {
    case EMULATED_DEVICE_GPIO: {
            EmulatorCommandGPIO_t *gpio_command = (EmulatorCommandGPIO_t *) &buffer[idx];
            *gpio_command = *((EmulatorCommandGPIO_t *) command);
            idx += sizeof(EmulatorCommandGPIO_t);
        }
        break;

    default:
        break;
    }

    commandEncoder_finish(buffer, idx);
    return idx;
}
