////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       05.12.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLOCK_H
#define CLOCK_H

#include <stdbool.h>
#include <stdint.h>

#define CLOCK_PERIODIC_TIMER_PERIOD_MS      1           ///< Defines, how ofter clock interrupt should be generated in miliseconds. Defines also minimal periodic callback timeout.

/// @brief General clock event callback. This type of function will be called by clock module, when event timeout expires.
typedef void (*ClockEventCallback_t)(void);

/// @brief Initializes periodic timer.
/// @return True on success, false otherwise.
bool clock_initPeriodicTimer();

/// @brief Adds new periodic callback.
/// @note This function is timer-safe, because it internally disables timer before adding callback. Should not be called in function, that is already registered as periodic callback.
/// @param [in] callback                                Callback to be registered.
/// @param [in] period_ms                               Defines, timeout for this event callback.
/// @param [in] count                                   Number of occurences, before it will be removed. If equals to -1, then it will be infinite.
/// @return True on success, false otherwise.
bool clock_addPeriodicCallback(ClockEventCallback_t callback, uint32_t period_ms, int32_t count);

/// @brief Adds new periodic callback.
/// @note This function is operates without disabling timer.
/// @param [in] callback                                Callback to be registered.
/// @param [in] period_ms                               Defines, timeout for this event callback.
/// @param [in] count                                   Number of events, that should be generated, before it will be automatically removed. If equals to -1, then it will be infinite.
/// @return True on success, false otherwise.
bool clock_addPeriodicCallbackAsync(ClockEventCallback_t callback, uint32_t period_ms, int32_t count);

/// @brief Removes periodic callback, before it is automatically removed.
/// @note This function is timer-safe, because it internally disables timer before adding callback. Should not be called in function, that is already registered as periodic callback.
/// @param [in] callback                                Callback to be removed.
/// @return True on success, false otherwise (ex. when there is no such callback).
bool clock_removePeriodicCallback(ClockEventCallback_t callback);

/// @brief Removes periodic callback, before it is automatically removed.
/// @note This function is operates without disabling timer.
/// @param [in] callback                                Callback to be removed.
/// @return True on success, false otherwise (ex. when there is no such callback).
bool clock_removePeriodicCallbackAsync(ClockEventCallback_t callback);

/// @brief Removes periodic callback with given index.
/// @param [in] index                                   Index of callback to be removed.
/// @return None.
void clock_removePeriodicEvent(int index);

/// @brief Updates deadline of every registered event and clears current timer tick value.
/// @return None.
void clock_updateEventsDeadline();

/// @brief Computers neariest deadline, that we should react to, by scanning all events.
/// @return None.
void clock_updateEarliestDeadline();

/// @brief Main periodic timer function. It is called every timer interrupt.
/// @return None.
void clock_processPeriodicEvents();

#endif
