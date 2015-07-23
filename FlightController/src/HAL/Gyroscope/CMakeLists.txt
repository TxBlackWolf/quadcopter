set(SOURCES
    Gyroscope.h
)

if(${FLIGHTCONTROLLER_USE_GYROSCOPE})
    add_subdirectory(${FLIGHTCONTROLLER_GYROSCOPE_DEVICE})
    message(STATUS "Enabling gyroscope: ${FLIGHTCONTROLLER_GYROSCOPE_DEVICE}")
else()
    message(STATUS "Gyroscope disabled")
endif()

RegisterModule()
