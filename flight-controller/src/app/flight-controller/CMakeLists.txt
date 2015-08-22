set(SOURCES
    ${APP_NAME}.c
)

register_executable()

link_target(${FLIGHTCONTROLLER_SRC_PATH}/board)
link_target(${FLIGHTCONTROLLER_DRIVERS_PATH}/lights)
