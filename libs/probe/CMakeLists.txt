set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_library(probe)
add_library(quite::probe ALIAS probe)
set_target_properties(probe PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(probe EXPORT_FILE_NAME quite/quite_probe_export.hpp)


target_sources(probe
    PUBLIC
        FILE_SET headers
            TYPE HEADERS
            BASE_DIRS include
            FILES
                include/quite/probe.hpp
        FILE_SET export_config
            TYPE HEADERS
            BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
            FILES
                ${CMAKE_CURRENT_BINARY_DIR}/quite/quite_probe_export.hpp
    PRIVATE
        src/probe.cpp
)
target_link_libraries(probe PRIVATE
    probeqt
)
