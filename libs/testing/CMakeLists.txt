add_library(quite_test)
add_library(quite::test ALIAS quite_test)
set_target_properties(quite_test PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(quite_test EXPORT_FILE_NAME quite/quite_test_export.hpp)

target_link_libraries(quite_test PUBLIC quite::client)

target_sources(quite_test
    PUBLIC
        FILE_SET headers
            TYPE HEADERS
            BASE_DIRS include
            FILES
                include/quite/test/application_manager.hpp
                include/quite/test/application.hpp
                include/quite/test/exceptions.hpp
                include/quite/test/object_query_builder.hpp
                include/quite/test/property.hpp
                include/quite/test/remote_object.hpp
        FILE_SET export_config
            TYPE HEADERS
            BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
            FILES
                ${CMAKE_CURRENT_BINARY_DIR}/quite/quite_test_export.hpp
)

target_include_directories(quite_test
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
)

add_subdirectory(src)
