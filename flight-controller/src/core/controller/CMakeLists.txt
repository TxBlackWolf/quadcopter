set(SOURCES
    commands_manager.c
    controller.c
)

register_module()

link_target(${FLIGHTCONTROLLER_BOARD_PATH})
link_target(${SKYVIPER_COMMAND_PATH})
