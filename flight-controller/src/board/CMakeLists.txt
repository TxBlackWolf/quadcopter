set(SOURCES
    console.h
)

set(MODULES
    ${FLIGHTCONTROLLER_BOARD}
)

RegisterComponent()

LinkTarget(${FLIGHTCONTROLLER_SRC_PATH}/hal)
 
