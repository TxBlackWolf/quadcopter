////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       23.07.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef BOARD_H
#define BOARD_H

#include "hal/gpio.h"
#include "hal/pwm.h"
#include "hal/timer.h"
#include "hal/uart.h"

#include <stdbool.h>

/// @brief System panic function.
/// @param [in]                         Panic message.
/// @return None.
void panic(const char *format, ...);

/// @brief Checks if this build is in debug mode.
/// @return True if yes, false otherwise.
bool board_isDebug();

/// @brief Checks if this build is in emulator mode.
/// @return True if yes, false otherwise.
bool board_isEmulator();

/// @brief Checks, if currently running system is in emergency mode.
/// @return True if yes, false otherwise.
bool board_isEmergencyBoot();

/// @brief Prints current system-wide clock settings.
/// @return None.
void board_showSystemClocks();

/// @brief Initializes all board specific features.
/// @return True on success, false otherwise.
bool board_init();

/// @brief Initializes periodic timer.
/// @param [in/out] timer_handle        Handle to timer, that should be used.
/// @return True on success, false otherwise.
bool board_periodicTimerInit(TimerHandle_t *timer_handle);

/// @brief Initializes communication link used in commands subsystem.
/// @param [in/out] uard_handle         Handle to uart, that should be used.
/// @return True on success, false otherwise.
bool board_commandsInit(UARTHandle_t *uart_handle);

/// @brief Initializes strobe light.
/// @param [in/out] gpio_handle	        Handle to GPIO, that should be used.
/// @param [in] gpio_general_config     GPIO configuration.
/// @return True on success, false otherwise.
bool board_strobeInit(GPIOHandle_t *gpio_handle, GPIOConfig_t *gpio_general_config);

/// @brief Initializes single engine.
/// @param [in/out] pwm_handle          Handle to PWM, that should be used.
/// @param [in] pwm_config              PWM configuration.
/// @param [in] gpio_general_config     GPIO configuration.
/// @return True on success, false otherwise.
bool board_engineInit(PWMHandle_t *pwm_handle, PWMConfig_t *pwm_config, GPIOConfig_t *gpio_general_config);

#endif
