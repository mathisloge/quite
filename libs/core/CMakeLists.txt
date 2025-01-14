add_library(quite_core)
add_library(quite::core ALIAS quite_core)
set_target_properties(quite_core PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(quite_core)

target_include_directories(quite_core PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(quite_core PUBLIC
    fmt::fmt
    quill::quill
)

target_sources(quite_core
    PUBLIC
        FILE_SET headers
            TYPE HEADERS
            BASE_DIRS include
            FILES
                include/quite/async_result.hpp
                include/quite/error.hpp
                include/quite/result.hpp
                include/quite/meta/meta_registry.hpp
                include/quite/meta/meta_types.hpp
        FILE_SET export_config
            TYPE HEADERS
            BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
            FILES
                ${CMAKE_CURRENT_BINARY_DIR}/quite_core_export.h
    PRIVATE
        src/error.cpp
        src/meta/meta_types.cpp
)
