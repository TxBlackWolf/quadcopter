set(SOURCES
    emulator_hal.c
    linux_timer.c
    network_uart.c
)

register_module()

target_link_libraries(${MODULE} rt)
