set(SOURCES
    emulator_gpio.c
    emulator_hal.c
    linux_timer.c
    network_uart.c
)

register_module()

link_target(rt)
link_target(${SKYVIPER_COMMON_PATH}/commands)
