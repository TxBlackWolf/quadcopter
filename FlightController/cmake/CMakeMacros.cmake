macro(RegisterExecutable)
    set(CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    get_filename_component(EXECUTABLE ${CURRENT_PATH} NAME)
    message(STATUS "Creating executable [${EXECUTABLE}]")
    
    add_executable(${EXECUTABLE} ${SOURCES})
endmacro()

macro(RegisterPacket)
    set(CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    get_filename_component(PACKET ${CURRENT_PATH} NAME)
    message(STATUS "Creating packet [${PACKET}]")

    foreach(COMPONENT ${COMPONENTS})
        add_subdirectory(${COMPONENT})
    endforeach()
endmacro()

macro(RegisterComponent)
    set(CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    get_filename_component(COMPONENT ${CURRENT_PATH} NAME)
    message(STATUS "Creating component [${COMPONENT}]")

    add_library(${COMPONENT} ${COMPONENT}.cpp ${SOURCES})
    set_property(TARGET ${COMPONENT} PROPERTY FOLDER ${COMPONENT})
    
    foreach(MODULE ${MODULES})
    
        add_subdirectory(${MODULE})
        set_property(TARGET ${MODULE} PROPERTY FOLDER ${COMPONENT})
        
        target_link_libraries(${COMPONENT} ${MODULE})
    endforeach()
endmacro()

macro(RegisterModule)
	set(CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
	get_filename_component(MODULE ${CURRENT_PATH} NAME)
    message(STATUS "Creating module [${MODULE}]")
    
    add_library(${MODULE} ${SOURCES})
endmacro()

macro(LinkTarget targetName)
    set(CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    get_filename_component(CURRENT_TARGET ${CURRENT_PATH} NAME)
    get_filename_component(LINKED_TARGET ${targetName} NAME)

    target_link_libraries(${CURRENT_TARGET} ${LINKED_TARGET})
endmacro()

macro(LinkExternalTarget targetName)
    set(CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    get_filename_component(CURRENT_TARGET ${CURRENT_PATH} NAME)
    set(LINKED_TARGET ${targetName})

    target_link_libraries(${CURRENT_TARGET} ${LINKED_TARGET})
endmacro()
