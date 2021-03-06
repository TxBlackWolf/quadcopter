////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       18.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMMAND_EMULATOR_H
#define COMMAND_EMULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "command_common.h"
#include "command_decoder.h"

#include <stdbool.h>
#include <stdint.h>

#define PIN_NAME_MAX_SIZE               16

/// @brief Type of emulated device, that this command describes.
typedef enum {
    EMULATED_DEVICE_GPIO,               ///< GPIO pins.
    EMULATED_DEVICE_COUNT               ///< Number of values is this enum. SHOULD BE LAST.
} EmulatedDevice_t;

/// @brief Header of emulator command.
typedef struct {
    EmulatedDevice_t device;            ///< Type of emulator subcommand. Describes, which emulated device does it describe.
} __attribute__((packed)) EmulatorHeader_t;

/// @brief Emulator command, that describe particular GPIO state.
typedef struct {
    uint32_t port;                      ///< GPIO port. By convention, it should be number starting from 1.
    uint32_t pin;                       ///< GPIO pin. By convention, it should be number starting from 0.
    uint32_t value;                     ///< GPIO state. Possible values: 0 or 1. Should be same as physical state.
    uint8_t name[PIN_NAME_MAX_SIZE];    ///< GPIO pin name.
} __attribute__((packed)) EmulatorCommandGPIO_t;

/// @brief Registers callback for given emulated device command.
/// @param [in] device                  Type of emulated device command, that callback is subscribed for.
/// @param [in] callback                Function to be called, when given subcommand is successfully parsed.
/// @return True on success, false otherwise.
bool command_registerEmulatorCallback(EmulatedDevice_t device, CommandCallback_t callback);

/// @brief Unregisters callback for given emulated device command.
/// @param [in] device                  Type of emulated device command, that callback is unsubscribed from.
/// @return True on success, false otherwise.
bool command_unregisterEmulatorCallback(EmulatedDevice_t device);

/// @brief Parses payload, that should contain emulator command.
/// @param [in] payload                 Buffer with command payload.
/// @param [in] size                    Payload buffer size.
/// @return True on success, false otherwise.
CommandDecoderError_t command_parseEmulator(uint8_t *payload, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif
