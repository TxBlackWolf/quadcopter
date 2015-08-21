set(SOURCES
    ${APP_NAME}.c
)

RegisterExecutable()

LinkTarget(${FLIGHTCONTROLLER_SRC_PATH}/board)
