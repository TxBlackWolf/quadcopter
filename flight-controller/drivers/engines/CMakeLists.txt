set(SOURCES
    engine.h
)

add_subdirectory(${FLIGHTCONTROLLER_ENGINES_DEVICE})
message(STATUS "Enabling engines: ${FLIGHTCONTROLLER_ENGINES_DEVICE}")

register_module()

link_target(${FLIGHTCONTROLLER_BOARD_PATH})

