////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       11.08.2015
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef UART_H
#define UART_H

#include "gpio.h"

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t UARTDevice_t;      ///< UART device id.
typedef uint32_t UARTBaudRate_t;    ///< UART baud rate.

/// @brief Possible UART data bits.
typedef enum {
    UART_DATA_BITS_7,               ///< UART data consists of 7 bits.
    UART_DATA_BITS_8,               ///< UART data consists of 8 bits.
    UART_DATA_BITS_9                ///< UART data consists of 9 bits.
} UARTDataBits_t;

/// @brief Possible UART stop bits.
typedef enum {
    UART_STOP_BITS_0_5,             ///< UART stop symbol cosnsists of 0,5 bit.
    UART_STOP_BITS_1,               ///< UART stop symbol cosnsists of 1 bit.
    UART_STOP_BITS_1_5,             ///< UART stop symbol cosnsists of 1,5 bit.
    UART_STOP_BITS_2                ///< UART stop symbol cosnsists of 2 bits.
} UARTStopBits_t;

/// @brief Possible UART partity.
typedef enum {
    UART_PARTITY_NONE,              ///< No partity bit is added.
    UART_PARTITY_EVEN,              ///< Partity bit is added to match even number of "1" bits.
    UART_PARTITY_ODD                ///< Partity bit is added to match odd number of "1" bits.
} UARTPartity_t;

/// @brief Possible UART flow control.
typedef enum {
    UART_FLOW_CONTROL_NONE,         ///< No flow control
    UART_FLOW_CONTROL_RTS_CTS,      ///< Hardware flow control that uses RTS/CTS lines.
    UART_FLOW_CONTROL_XON_XOFF      ///< Software flow control.
} UARTFlowControl_t;

/// @brief Possible UART direction settings.
typedef enum {
    UART_DIRECTION_READ,            ///< Read-only mode.
    UART_DIRECTION_WRITE,           ///< Write-only mode.
    UART_DIRECTION_BIDIRECTIONAL    ///< Read-write mode.
} UARTDirection_t;

/// @brief UART synchronization mode.
typedef enum {
    UART_MODE_SYNCHRONOUS,          ///< Device works in synchronous mode (USART).
    UART_MODE_ASYNCHRONOUS          ///< Device works in asynchronous mode (UART).
} UARTMode_t;

/// @brief UART configuration structure.
typedef struct {
    UARTBaudRate_t baud_rate;       ///< Desired baud rate.
    UARTDataBits_t data_bits;       ///< Desired data bits.
    UARTStopBits_t stop_bits;       ///< Desired stop bits.
    UARTPartity_t parity;           ///< Desired partity control.
    UARTFlowControl_t flow_control; ///< Desired flow control.
    UARTDirection_t direction;      ///< Desired device direction.
    UARTMode_t mode;                ///< Desired device mode.
} UARTConfig_t;

/// @brief UART device handle.
typedef struct {
    UARTDevice_t device;            ///< Device id.
    GPIOHandle_t gpio_tx;           ///< GPIO handle for transmitting pin.
    GPIOHandle_t gpio_rx;           ///< GPIO handle for receiving pin.
    void *private_data;             ///< Pointer to driver private data.
} UARTHandle_t;

/// @brief Activates uart device.
/// @param [in] handle          UART device to be activated.
void uart_activate(UARTHandle_t *handle);

/// @brief Deactivates uart device.
/// @param [in] handle          UART device to be deactivated.
void uart_deactivate(UARTHandle_t *handle);

/// @brief Sends given data to given device.
/// @note Data argument is 16-bit wide. This is reserved only for situation,
///       when device is configured with 9-bit data symbols. Data will be caseted to match settings.
/// @param [in] handle          UART device.
/// @param [in] data            Data to be sent.
/// @return True on success, false otherwise.
bool uart_send(UARTHandle_t *handle, uint16_t data);

/// @brief Receives one symbol from given device.
/// @note Data argument is 16-bit wide. This is reserved only for situation,
///       when device is configured with 9-bit data symbols. Data will be caseted to match settings.
/// @param [in] handle          UART device.
/// @param [out] data           Buffer for received data.
/// @return True on success, false otherwise.
bool uart_receive(UARTHandle_t *handle, uint16_t *data);

#endif
