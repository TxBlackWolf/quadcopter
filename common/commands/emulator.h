////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       18.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef EMULATOR_H
#define EMULATOR_H

#include "commands.h"

#include <stdbool.h>
#include <stdint.h>

/// @brief General callback for commands. It should be called by command framework, after it
///        detects specific command.
/// @param [in] buffer              Payload of detected command.
/// @param [in] size                Size of command payload.
/// @return None.
typedef void (*CommandCallback_t)(uint8_t *buffer, uint32_t size);

/// @brief Type of emulated device, that this emulator command describes.
typedef enum {
    EMULATED_DEVICE_GPIO,           ///< GPIO pins.
    EMULATED_DEVICE_COUNT           ///< Number of values is this enum. SHOULD BE LAST.
} EmulatedDevice_t;

/// @brief Header of emulator command.
typedef struct {
    EmulatedDevice_t device;        ///< Type of emulator subcommand. Describes, which emulated device does it describe.
} __attribute__((packed)) EmulatorCommand_t;

/// @brief Emulator command, that describe particular GPIO state.
typedef struct {
    uint32_t port;                  ///< GPIO port. By convention, it should be number starting from 1.
    uint32_t pin;                   ///< GPIO pin. By convention, it should be number starting from 0.
    uint32_t value;                 ///< GPIO state. Possible values: 0 or 1. Should be same as physical state.
    uint32_t name_size;             ///< Size of the following GPIO pin name. If 0, then there is no name.
} __attribute__((packed)) EmulatorCommandGPIO_t;

/// @brief Registers callback for given emulated device command.
/// @param [in] device              Type of emulated device command, that callback is subscribed for.
/// @param [in] callback            Function to be called, when given subcommand is successfully parsed.
/// @return True on success, false otherwise.
bool command_registerEmulatorCallback(EmulatedDevice_t device, CommandCallback_t callback);

/// @brief Unregisters callback for given emulated device command.
/// @param [in] device              Type of emulated device command, that callback is unsubscribed from.
/// @return True on success, false otherwise.
bool command_unregisterEmulatorCallback(EmulatedDevice_t device);

/// @brief Parses payload, that should contain emulator command.
/// @param [in] payload             Buffer with command payload.
/// @param [in] size                Payload buffer size.
/// @return True on success, false otherwise.
bool command_parseEmulator(uint8_t *payload, uint32_t size);

#endif
