message(STATUS "  ---> Generating header with supported drivers")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/board_drivers_support.h.in ${CMAKE_CURRENT_SOURCE_DIR}/board_drivers_support.h)

message(STATUS "  ---> Generating header with board pinout")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/board_pinout.h.in ${CMAKE_CURRENT_SOURCE_DIR}/board_pinout.h)

set(SOURCES
    assert.h
    board.h
    board_drivers_support.h
    board_pinout.h
    clock.c
    console.h
)

set(MODULES
    ${FLIGHTCONTROLLER_BOARD}
)

register_component()

link_target(${FLIGHTCONTROLLER_DRIVERS_PATH}/engines)
link_target(${FLIGHTCONTROLLER_DRIVERS_PATH}/lights)
link_target(${FLIGHTCONTROLLER_HAL_PATH})
link_target(${FLIGHTCONTROLLER_UTILS_PATH})
