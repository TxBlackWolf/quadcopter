set(SOURCES
    ${APP_NAME}.c
)

register_executable()

link_target(${FLIGHTCONTROLLER_BOARD_PATH})

link_target(${FLIGHTCONTROLLER_DRIVERS_PATH}/engines)
link_target(${FLIGHTCONTROLLER_DRIVERS_PATH}/lights)
