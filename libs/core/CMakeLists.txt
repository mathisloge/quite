add_library(quite_core SHARED)
add_library(quite::core ALIAS quite_core)

target_compile_definitions(quite_core PUBLIC ASIO_TO_EXEC_USE_BOOST)
target_compile_features(quite_core
    PUBLIC cxx_std_23
)
set_target_properties(quite_core PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    VISIBILITY_INLINES_HIDDEN ON
)
generate_export_header(quite_core EXPORT_FILE_NAME quite/quite_core_export.hpp)
configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/version.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/quite/version.hpp"
)

target_link_libraries(quite_core PUBLIC
    fmt::fmt
    quill::quill
    Boost::headers
    EnTT::EnTT
    STDEXEC::stdexec
    stb::stb
)

target_sources(quite_core
    PUBLIC
        FILE_SET headers
            TYPE HEADERS
            BASE_DIRS include
            FILES
                include/quite/asio2exec.hpp
                include/quite/async_result.hpp
                include/quite/error.hpp
                include/quite/result.hpp
                include/quite/setup_logger.hpp
                include/quite/logger.hpp
                include/quite/image.hpp
                include/quite/meta_any_formatter.hpp
                include/quite/meta/meta_registry.hpp
                include/quite/meta/meta_types.hpp

                include/quite/value/value_registry.hpp
                include/quite/value/generic_value_class.hpp
                include/quite/value/object_query.hpp

                include/quite/injectors/mouse_injector.hpp
        FILE_SET export_config
            TYPE HEADERS
            BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
            FILES
                ${CMAKE_CURRENT_BINARY_DIR}/quite/quite_core_export.hpp
                ${CMAKE_CURRENT_BINARY_DIR}/quite/version.hpp
    PRIVATE
        src/error.cpp
        src/meta/meta_types.cpp
        src/logger.cpp
        src/image.cpp
        src/value/value_registry.cpp
        src/value/object_query.cpp
)
