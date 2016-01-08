set(SOURCES
    emulator_hal.c
    linux_timer.c
)

register_module()

target_link_libraries(${MODULE} rt)
