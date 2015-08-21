set(SOURCES
    magnetometer.h
)

if(${FLIGHTCONTROLLER_USE_MAGNETOMETER})
    add_subdirectory(${FLIGHTCONTROLLER_MAGNETOMETER_DEVICE})
    message(STATUS "Enabling magnetometer: ${FLIGHTCONTROLLER_MAGNETOMETER_DEVICE}")
else()
    message(STATUS "Magnetometer disabled")
endif()

RegisterModule()
