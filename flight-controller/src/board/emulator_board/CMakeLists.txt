set(SOURCES
    emulator_board.c
    emulator_board_pinout.h
    printf_console.c
    signal_handlers.c
)

register_module()

target_link_libraries(${MODULE} rt)
