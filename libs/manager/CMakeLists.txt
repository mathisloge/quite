add_library(quite_manager)
add_library(quite::manager ALIAS quite_manager)
set_target_properties(quite_manager PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(quite_manager EXPORT_FILE_NAME quite/quite_manager_export.hpp)

target_link_libraries(quite_manager PUBLIC
    quite::core
)

target_sources(quite_manager
    PUBLIC
        FILE_SET headers
            TYPE HEADERS
            BASE_DIRS include
            FILES
                include/quite/manager/application_manager.hpp
                include/quite/manager/application.hpp
        FILE_SET export_config
            TYPE HEADERS
            BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
            FILES
                ${CMAKE_CURRENT_BINARY_DIR}/quite/quite_manager_export.hpp
    PRIVATE
        src/application_manager.cpp
        src/application_impl.hpp
        src/application_impl.cpp
)
