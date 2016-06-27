////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       27.06.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SYSTEM_STATUS_H
#define SYSTEM_STATUS_H

#include <stdbool.h>

/// @brief Structure describing status of hardware and software on system level.
typedef struct {
    // Info about compiled firmware.
    const char *firmware_name;              ///< Firmware name.
    const char *firmware_version;           ///< Firmware version.
    bool is_debug;                          ///< True if debug, false otherwise.
    bool is_emulator;                       ///< True if emulator, false otherwise.

    bool boot_completed;                    ///< True if booting finished without errors, false otherwise.

    // Info about configured drivers.
    const char *engines_name;               ///< Name of engines used in device.
} SystemStatus_t;

/// @brief Initializes all meta data of system status, that are available at booting level.
void systemStatus_init();

/// @brief Marks that booting process is complete and device is ready to go.
void systemStatus_bootingCompleted();

/// @brief Sets name of engines used in device.
/// @param [in] name            C-string descriving engines name.
void systemStatus_setEnginesName(const char *name);

#endif
