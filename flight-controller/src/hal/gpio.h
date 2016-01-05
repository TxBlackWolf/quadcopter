//---------------------------------------------------------------------------------------------------------------
//
// Filename   : gpio.h
// Author     : Kuba Sejdak
// Created on : 11.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t GPIOPort_t;
typedef uint32_t GPIOPin_t;

// Pin mode.
typedef enum {
    GPIO_DIRECTION_IN  = 0x0,
    GPIO_DIRECTION_OUT = 0x1
} GPIODirection_t;

// Pullup/pulldown resistors.
typedef enum {
    GPIO_RESISTOR_NONE     = 0x1,
    GPIO_RESISTOR_PULLUP   = 0x2,
    GPIO_RESISTOR_PULLDOWN = 0x3
} GPIOResistorType_t;

// Pin configuration structure.
typedef struct {
    GPIODirection_t direction;
    GPIOResistorType_t resistor_type;
} GPIOConfig_t;

// Pin handle.
typedef struct {
    GPIOPort_t port;
    GPIOPin_t pin;
    const char *name;
} GPIOHandle_t;

void gpio_activate(GPIOHandle_t *handle);
void gpio_deactivate(GPIOHandle_t *handle);

bool gpio_readPin(GPIOHandle_t *handle);
uint16_t gpio_readPort(GPIOHandle_t *handle);

bool gpio_writePin(GPIOHandle_t *handle, bool value);
bool gpio_writePort(GPIOHandle_t *handle, uint16_t value);

void gpio_pinConfigLock(GPIOHandle_t *handle);

#endif
