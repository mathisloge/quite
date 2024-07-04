add_library(loggerlib SHARED)
add_library(quite::logger ALIAS loggerlib)
set_target_properties(loggerlib PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(loggerlib)

target_include_directories(loggerlib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(loggerlib PUBLIC
    spdlog::spdlog
)

target_sources(loggerlib
    PRIVATE
        src/logger.cpp
)
