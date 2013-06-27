macro(vanetza_module NAME)
    set(_sources ${ARGN})
    add_library(vanetza_${NAME} SHARED ${_sources})
    add_library(vanetza_${NAME}_static STATIC ${_sources})
endmacro()

macro(vanetza_module_dependencies NAME)
    set(_deps ${ARGN})
    foreach(_dep ${_deps})
        target_link_libraries(vanetza_${NAME} ${_dep})
        target_link_libraries(vanetza_${NAME}_static ${_dep})
    endforeach()
endmacro()

macro(vanetza_intermodule_dependencies NAME)
    set(_modules ${ARGN})
    foreach(_module ${_modules})
        target_link_libraries(vanetza_${NAME} vanetza_${_module})
        target_link_libraries(vanetza_${NAME}_static vanetza_${_module}_static)
    endforeach()
endmacro()

macro(vanetza_module_property NAME)
    set_property(TARGET vanetza_${NAME} vanetza_${NAME}_static
        APPEND PROPERTY ${PROPERTY} ${ARGN})
endmacro()

macro(target_link_vanetza TARGET)
    set(_modules ${ARGN})
    foreach(_module ${_modules})
        target_link_libraries(${TARGET} vanetza_${_module}_static)
    endforeach()
endmacro()