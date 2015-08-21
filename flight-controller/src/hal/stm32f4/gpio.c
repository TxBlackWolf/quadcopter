//---------------------------------------------------------------------------------------------------------------
//
// Filename   : GPIO.c
// Author     : Kuba Sejdak
// Created on : 11.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "hal/gpio.h"
#include "hal/rcc.h"
#include "hal/stm32f4/CMSIS/stm32f4xx.h"

typedef GPIO_TypeDef GPIO_t;

//---------------------------------------------------------------------------------------------------------------
// PLATFORM FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

#define STM32F4_GPIO_PORTS_NUM      9

int gpio_getPortsNum()
{
    return STM32F4_GPIO_PORTS_NUM;
}

//---------------------------------------------------------------------------------------------------------------
// HELPER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

GPIO_t *gpio_getRegisters(GPIOPort_t port)
{
    switch(port)
    {
    case GPIO_PORT_A: return GPIOA;
    case GPIO_PORT_B: return GPIOB;
    case GPIO_PORT_C: return GPIOC;
    case GPIO_PORT_D: return GPIOD;
    case GPIO_PORT_E: return GPIOE;
    case GPIO_PORT_F: return GPIOF;
    case GPIO_PORT_G: return GPIOG;
    case GPIO_PORT_H: return GPIOH;
    case GPIO_PORT_I: return GPIOI;
    }

    return 0;
}

uint32_t gpio_getPinNumber(GPIOPin_t pin)
{
    switch(pin)
    {
    case GPIO_PIN_0: return 0;
    case GPIO_PIN_1: return 1;
    case GPIO_PIN_2: return 2;
    case GPIO_PIN_3: return 3;
    case GPIO_PIN_4: return 4;
    case GPIO_PIN_5: return 5;
    case GPIO_PIN_6: return 6;
    case GPIO_PIN_7: return 7;
    case GPIO_PIN_8: return 8;
    case GPIO_PIN_9: return 9;
    case GPIO_PIN_10: return 10;
    case GPIO_PIN_11: return 11;
    case GPIO_PIN_12: return 12;
    case GPIO_PIN_13: return 13;
    case GPIO_PIN_14: return 14;
    case GPIO_PIN_15: return 15;
    }

    return -1;
}

//---------------------------------------------------------------------------------------------------------------
// INTERFACE FUNCTIONS
//---------------------------------------------------------------------------------------------------------------

void gpio_setPinFunction(GPIOPort_t port, GPIOPin_t pin, uint8_t function)
{
    GPIO_t *gpio = gpio_getRegisters(port);
    uint32_t pin_number = gpio_getPinNumber(pin);
    uint32_t value = (function << (pin_number & 0x7) * 4);
    uint32_t afr_half = pin_number >> 3;
    gpio->AFR[afr_half] |= value;
}

GPIOHandle_t gpio_init(GPIOConfig_t config)
{
    // Set pin alternate function.
    gpio_setPinFunction(config.port, config.pin, config.function);

    GPIO_t *gpio = gpio_getRegisters(config.port);

    // Set mode.
    gpio->MODER |= (config.mode << (config.pin * 2));

    if(config.mode == GPIO_MODE_OUT || config.mode == GPIO_MODE_ALTERNATE)
    {
        // Set speed.
        gpio->OSPEEDR |= (config.speed << (config.pin * 2));

        // Set output mode.
        gpio->OTYPER |= (config.output_type << config.pin);
    }

    // Set pullup/pulldown resistor.
    gpio->PUPDR |= (config.resistor_type << (config.pin * 2));

    GPIOHandle_t handle;
    handle.port = config.port;
    handle.pin = config.pin;
    return handle;
}

void gpio_deactivate(GPIOHandle_t handle)
{
    uint32_t port_clock = 0;
    switch(handle.port)
    {
    case GPIO_PORT_A:   port_clock = RCC_AHB1_PERIPHERAL_GPIOA; break;
    case GPIO_PORT_B:   port_clock = RCC_AHB1_PERIPHERAL_GPIOB; break;
    case GPIO_PORT_C:   port_clock = RCC_AHB1_PERIPHERAL_GPIOC; break;
    case GPIO_PORT_D:   port_clock = RCC_AHB1_PERIPHERAL_GPIOD; break;
    case GPIO_PORT_E:   port_clock = RCC_AHB1_PERIPHERAL_GPIOE; break;
    case GPIO_PORT_F:   port_clock = RCC_AHB1_PERIPHERAL_GPIOF; break;
    case GPIO_PORT_G:   port_clock = RCC_AHB1_PERIPHERAL_GPIOG; break;
    case GPIO_PORT_H:   port_clock = RCC_AHB1_PERIPHERAL_GPIOH; break;
    case GPIO_PORT_I:   port_clock = RCC_AHB1_PERIPHERAL_GPIOI; break;
    }

    rcc_resetPeripheralAHB1(port_clock, false);
}

bool gpio_readPin(GPIOHandle_t handle)
{
    GPIO_t *gpio = gpio_getRegisters(handle.port);
    return (gpio->IDR & handle.pin);
}

uint16_t gpio_readPort(GPIOPort_t port)
{
    GPIO_t *gpio = gpio_getRegisters(port);
    return gpio->IDR;
}

bool gpio_writePin(GPIOHandle_t handle, bool value)
{
    GPIO_t *gpio = gpio_getRegisters(handle.port);
    if(value)
        gpio->ODR |= handle.pin;
    else
        gpio->ODR &= ~handle.pin;

    return (gpio->ODR & handle.pin);
}

bool gpio_writePort(GPIOPort_t port, uint16_t value)
{
    GPIO_t *gpio = gpio_getRegisters(port);
    gpio->ODR = value;

    return (gpio->ODR == value);
}

void gpio_pinConfigLock(GPIOHandle_t handle)
{
    GPIO_t *gpio = gpio_getRegisters(handle.port);
    volatile uint32_t value = (1 << 16);

    value |= handle.pin;
    gpio->LCKR = value;
    gpio->LCKR = handle.pin;
    gpio->LCKR = value;
    value = gpio->LCKR;
    value = gpio->LCKR;
}
