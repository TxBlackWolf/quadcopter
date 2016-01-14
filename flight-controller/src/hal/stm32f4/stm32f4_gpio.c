//=============================================================================================
//
// Filename   : stm32f4_gpio.c
// Author     : Kuba Sejdak
// Created on : 11.08.2015
//
// This file is a part of SkyViper project.
//
// %LICENSE%
//
//=============================================================================================

#include "stm32f4_gpio.h"
#include "stm32f4_gpio_functions.h"
#include "stm32f4_rcc.h"
#include "board/console.h"
#include "CMSIS/stm32f4xx.h"

typedef GPIO_TypeDef GPIO_t;

//=============================================================================================
// HELPER FUNCTIONS
//=============================================================================================

GPIO_t *stm32f4_gpioGetRegisters(GPIOPort_t port)
{
    switch(port) {
    case STM32F4_GPIO_PORT_A:   return GPIOA;
    case STM32F4_GPIO_PORT_B:   return GPIOB;
    case STM32F4_GPIO_PORT_C:   return GPIOC;
    case STM32F4_GPIO_PORT_D:   return GPIOD;
    case STM32F4_GPIO_PORT_E:   return GPIOE;
    case STM32F4_GPIO_PORT_F:   return GPIOF;
    case STM32F4_GPIO_PORT_G:   return GPIOG;
    case STM32F4_GPIO_PORT_H:   return GPIOH;
    case STM32F4_GPIO_PORT_I:   return GPIOI;
    }

    return 0;
}

uint32_t stm32f4_gpioGetPinMask(GPIOPin_t pin)
{
    return (1 << pin);
}

void stm32f4_gpioSetPinFunction(GPIOHandle_t *handle, uint8_t function)
{
    GPIO_t *gpio = stm32f4_gpioGetRegisters(handle->port);
    uint32_t value = (function << (handle->pin & 0x7) * 4);
    uint32_t afr_half = handle->pin >> 3;
    gpio->AFR[afr_half] |= value;
}

void stm32f4_gpioEnableClock(GPIOPort_t port, bool value)
{
    uint32_t ahb1_peripheral = 0;
    switch(port) {
    case STM32F4_GPIO_PORT_A:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOA; break;
    case STM32F4_GPIO_PORT_B:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOB; break;
    case STM32F4_GPIO_PORT_C:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOC; break;
    case STM32F4_GPIO_PORT_D:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOD; break;
    case STM32F4_GPIO_PORT_E:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOE; break;
    case STM32F4_GPIO_PORT_F:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOF; break;
    case STM32F4_GPIO_PORT_G:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOG; break;
    case STM32F4_GPIO_PORT_H:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOH; break;
    case STM32F4_GPIO_PORT_I:   ahb1_peripheral = RCC_AHB1_PERIPHERAL_GPIOI; break;
    }

    stm32f4_rccEnablePeripheralClockAHB1(ahb1_peripheral, value);
}

//=============================================================================================
// INTERFACE FUNCTIONS
//=============================================================================================

bool stm32f4_gpioInit(GPIOHandle_t *handle, STM32F4_GPIOConfig_t config)
{
    stm32f4_gpioEnableClock(handle->port, true);

    if(config.function != GPIO_DIGITAL_PIN) {
        if(config.function < 0) {
            console_write("gpio: Bad alternate function number: %d\n", config.function);
            return false;
        }

        stm32f4_gpioSetPinFunction(handle, config.function);
    }

    GPIO_t *gpio = stm32f4_gpioGetRegisters(handle->port);

    gpio->MODER |= (config.mode << (handle->pin * 2));

    if(config.mode == GPIO_MODE_OUT || config.mode == GPIO_MODE_ALTERNATE) {
        gpio->OSPEEDR |= (config.speed << (handle->pin * 2));
        gpio->OTYPER |= (config.output_type << handle->pin);
    }

    gpio->PUPDR |= (config.general_config.resistor_type << (handle->pin * 2));

    return true;
}

void gpio_activate(GPIOHandle_t *handle)
{
    stm32f4_gpioEnableClock(handle->port, true);
}

void gpio_deactivate(GPIOHandle_t *handle)
{
    stm32f4_gpioEnableClock(handle->port, false);
}

bool gpio_readPin(GPIOHandle_t *handle)
{
    GPIO_t *gpio = stm32f4_gpioGetRegisters(handle->port);
    uint16_t pin_mask = stm32f4_gpioGetPinMask(handle->pin);
    return (gpio->IDR & pin_mask);
}

uint16_t gpio_readPort(GPIOHandle_t *handle)
{
    GPIO_t *gpio = stm32f4_gpioGetRegisters(handle->port);
    return gpio->IDR;
}

bool gpio_writePin(GPIOHandle_t *handle, bool value)
{
    GPIO_t *gpio = stm32f4_gpioGetRegisters(handle->port);
    uint16_t pin_mask = stm32f4_gpioGetPinMask(handle->pin);
    if(value)
        gpio->ODR |= pin_mask;
    else
        gpio->ODR &= ~pin_mask;

    return (gpio->ODR & pin_mask);
}

bool gpio_writePort(GPIOHandle_t *handle, uint16_t value)
{
    GPIO_t *gpio = stm32f4_gpioGetRegisters(handle->port);
    gpio->ODR = value;

    return (gpio->ODR == value);
}

void gpio_pinConfigLock(GPIOHandle_t *handle)
{
    GPIO_t *gpio = stm32f4_gpioGetRegisters(handle->port);
    volatile uint32_t value = (1 << 16);

    value |= handle->pin;
    gpio->LCKR = value;
    gpio->LCKR = handle->pin;
    gpio->LCKR = value;
    value = gpio->LCKR;
    value = gpio->LCKR;

    console_write("gpio: GPIO P%d.%d config locked (%s)\n", handle->port, handle->pin, handle->name);
}
