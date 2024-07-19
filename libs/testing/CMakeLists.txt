add_library(quite_testing)
add_library(quite::testing ALIAS quite_testing)
set_target_properties(quite_testing PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(quite_testing)

target_link_libraries(quite_testing PUBLIC quite::quite)

target_include_directories(quite_testing PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

add_subdirectory(src)
