////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       18.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMMAND_CONTROL_H
#define COMMAND_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "command_common.h"
#include "command_decoder.h"

#include <stdbool.h>
#include <stdint.h>

/// @brief Type of control event, that this command describes.
typedef enum {
    CONTROL_EVENT_THROTTLE,             ///< Throttle.
    CONTROL_EVENT_COUNT                 ///< Number of values is this enum. SHOULD BE LAST.
} ControlEvent_t;

/// @brief Header of control command.
typedef struct {
    ControlEvent_t event;               ///< Type of control subcommand. Describes, which control event does it describe.
} __attribute__((packed)) ControlHeader_t;

/// @brief Control command, that describe engines throttle.
typedef struct {
    int8_t throttle;                    ///< Throttle percentage. It should be number from range 0-100 with sign.
} __attribute__((packed)) ControlCommandThrottle_t;

/// @brief Registers callback for given control event command.
/// @param [in] event                  Type of control event command, that callback is subscribed for.
/// @param [in] callback               Function to be called, when given subcommand is successfully parsed.
/// @return True on success, false otherwise.
bool command_registerControlCallback(ControlEvent_t event, CommandCallback_t callback);

/// @brief Unregisters callback for given control event command.
/// @param [in] event                  Type of control event command, that callback is unsubscribed from.
/// @return True on success, false otherwise.
bool command_unregisterControlCallback(ControlEvent_t event);

/// @brief Parses payload, that should contain emulator command.
/// @param [in] payload                 Buffer with command payload.
/// @param [in] size                    Payload buffer size.
/// @return True on success, false otherwise.
CommandDecoderError_t command_parseControl(uint8_t *payload, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif
