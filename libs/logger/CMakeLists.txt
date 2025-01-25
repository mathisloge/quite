add_library(quite_logger)
add_library(quite::logger ALIAS quite_logger)
set_target_properties(quite_logger PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(quite_logger)

target_include_directories(quite_logger PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(quite_logger PUBLIC
    fmt::fmt
    quill::quill
)

target_sources(quite_logger
    PRIVATE
        src/logger.cpp
)

install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/quite_logger_export.h" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
