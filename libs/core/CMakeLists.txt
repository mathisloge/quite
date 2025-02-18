add_library(quite_core)
add_library(quite::core ALIAS quite_core)
set_target_properties(quite_core PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(quite_core EXPORT_FILE_NAME quite/quite_core_export.hpp)
configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/version.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/quite/version.hpp"
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
                include/quite/setup_logger.hpp
                include/quite/logger.hpp
                include/quite/meta/meta_registry.hpp
                include/quite/meta/meta_types.hpp
                include/quite/details/process.hpp

                include/quite/value/value_registry.hpp
                include/quite/value/generic_value_class.hpp
                include/quite/value/object_query.hpp
        FILE_SET export_config
            TYPE HEADERS
            BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
            FILES
                ${CMAKE_CURRENT_BINARY_DIR}/quite/quite_core_export.hpp
                ${CMAKE_CURRENT_BINARY_DIR}/quite/version.hpp
    PRIVATE
        src/error.cpp
        src/meta/meta_types.cpp
        src/details/process.cpp
        src/logger.cpp
        src/value/value_registry.cpp
        src/value/object_query.cpp
)
