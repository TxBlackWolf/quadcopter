set(SOURCES
    Barometer.h
)

if(${FLIGHTCONTROLLER_USE_BAROMETER})
    add_subdirectory(${FLIGHTCONTROLLER_BAROMETER_DEVICE})
    message(STATUS "Enabling barometer: ${FLIGHTCONTROLLER_BAROMETER_DEVICE}")
else()
    message(STATUS "Barometer disabled")
endif()

RegisterModule()
