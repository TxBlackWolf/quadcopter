////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.08.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t GPIOPort_t;            ///< GPIO port id.
typedef uint32_t GPIOPin_t;             ///< GPIO pin id.

/// @brief Possible GPIO pin directions.
typedef enum {
    GPIO_DIRECTION_IN,                  ///< GPIO input pin (relative to MCU).
    GPIO_DIRECTION_OUT                  ///< GPIO output pin (relative to MCU).
} GPIODirection_t;

/// @brief GPIO pullup/pulldown resistors settings.
typedef enum {
    GPIO_RESISTOR_NONE,                 ///< Pin has no internal pullup/pulldown resistor.
    GPIO_RESISTOR_PULLUP,               ///< Pin in internally pulled-up.
    GPIO_RESISTOR_PULLDOWN              ///< Pin in internally pulled-down.
} GPIOResistorType_t;

/// @brief GPIO configuration structure.
typedef struct {
    GPIODirection_t direction;          ///< Desired pin direction.
    GPIOResistorType_t resistor_type;   ///< Desired resistor type.
} GPIOConfig_t;

/// @brief GPIO device handle.
typedef struct {
    GPIOPort_t port;                    ///< GPIO port id.
    GPIOPin_t pin;                      ///< GPIO pin id.
    const char *name;                   ///< Optional pin name.
    void *private_data;                 ///< Pointer to driver private data.
} GPIOHandle_t;

/// @brief Activates GPIO device.
/// @param [in] handle          GPIO device to be activated.
void gpio_activate(GPIOHandle_t *handle);

/// @brief Deactivates GPIO device.
/// @param [in] handle          GPIO device to be deactivated.
void gpio_deactivate(GPIOHandle_t *handle);

/// @brief Reads value from one pin in given device.
/// @param [in] handle          GPIO device to be read from.
/// @return True if pin has HIGH value, false otherwise.
bool gpio_readPin(GPIOHandle_t *handle);

/// @brief Reads value from whole port in given device.
/// @param [in] handle          GPIO device to be read from.
/// @return 1 for each pin, that has HIGH value, 0 otherwise.
uint16_t gpio_readPort(GPIOHandle_t *handle);

/// @brief Writes value on one pin in given device.
/// @param [in] handle          GPIO device to be written to.
/// @param [in] value           Desired pin state.
/// @return True on success, false otherwise.
bool gpio_writePin(GPIOHandle_t *handle, bool value);

/// @brief Writes value to whole port in given device.
/// @param [in] handle          GPIO device to be written to.
/// @param [in] value           Desired port state.
/// @return True on success, false otherwise.
bool gpio_writePort(GPIOHandle_t *handle, uint16_t value);

/// @brief Locks configuration for given device.
/// @param [in] handle          GPIO device for which configuration should be locked.
void gpio_pinConfigLock(GPIOHandle_t *handle);

#endif
