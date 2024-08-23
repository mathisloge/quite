add_library(loggerlib)
add_library(quite::logger ALIAS loggerlib)
set_target_properties(loggerlib PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(loggerlib)

target_include_directories(loggerlib PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(loggerlib PUBLIC
    fmt::fmt
    quill::quill
)

target_sources(loggerlib
    PRIVATE
        src/logger.cpp
)

install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/loggerlib_export.h" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
