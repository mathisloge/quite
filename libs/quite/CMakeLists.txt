add_library(quite_client)
add_library(quite::client ALIAS quite_client)
target_compile_features(quite_client
    PUBLIC cxx_std_23
)
set_target_properties(quite_client PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    VISIBILITY_INLINES_HIDDEN ON
)
generate_export_header(quite_client EXPORT_FILE_NAME quite/quite_client_export.hpp)

target_include_directories(quite_client
PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
    ${Stb_INCLUDE_DIR}
)

target_sources(quite_client
    PUBLIC
        FILE_SET headers
            TYPE HEADERS
            BASE_DIRS include
            FILES
                include/quite/testing/verification_point.hpp
                include/quite/utils/dump_properties.hpp
                include/quite/probe.hpp
                include/quite/probe_handle.hpp
                include/quite/probe_manager.hpp
                include/quite/image_utils.hpp
                include/quite/property.hpp
                include/quite/quite.hpp
                include/quite/remote_object.hpp
        FILE_SET export_config
            TYPE HEADERS
            BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
            FILES
                ${CMAKE_CURRENT_BINARY_DIR}/quite/quite_client_export.hpp
    PRIVATE
        src/quite.cpp
        src/basic_probe.hpp
        src/basic_probe.cpp
        src/probe_handle.cpp
        src/probe_manager.cpp
        src/property.cpp
        src/context.cpp
        src/context.hpp
        src/remote_object.cpp
        src/image_utils.cpp
)

target_link_libraries(quite_client PRIVATE
    Boost::headers
    nlohmann_json::nlohmann_json
    quite::protocol
PUBLIC
    quite::core
    quite::manager
)
add_subdirectory(src/grpc_impl)
add_subdirectory(src/utils)
add_subdirectory(src/testing)
