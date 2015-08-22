set(SOURCES
    engine.h
)

if(${FLIGHTCONTROLLER_USE_ENGINES})
    add_subdirectory(${FLIGHTCONTROLLER_ENGINES_DEVICE})
    message(STATUS "Enabling engines: ${FLIGHTCONTROLLER_ENGINES_DEVICE}")
else()
    message(STATUS "Engines disabled")
endif()

register_module()
