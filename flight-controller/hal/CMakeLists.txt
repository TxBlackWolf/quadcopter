set(SOURCES
    gpio.h
    pwm.h
    rcc.h
    timer.h
    uart.h
)

set(MODULES
    ${FLIGHTCONTROLLER_HAL}
)

register_component()
