////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       24.04.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMMAND_ENCODER_H
#define COMMAND_ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "command_emulator.h"

#include <stdint.h>

/// @brief Creates emulator command.
/// @param [in/out] buffer          Buffer for command.
/// @param [in] device              Emulated device type.
/// @param [in] command             Specific emulator command.
/// @return Size of created command.
int commandEncoder_createEmulatorCommand(uint8_t *buffer, EmulatedDevice_t device, void *command);

#ifdef __cplusplus
}
#endif

#endif 
