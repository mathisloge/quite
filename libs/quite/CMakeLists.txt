add_library(quite_client)
add_library(quite::client ALIAS quite_client)
set_target_properties(quite_client PROPERTIES
    POSITION_INDEPENDENT_CODE ON
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
                include/quite/application.hpp
                include/quite/application_manager.hpp
                include/quite/asio2exec.hpp
                include/quite/image.hpp
                include/quite/indirect.hpp
                include/quite/object_query.hpp
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
        src/application.cpp
        src/application_manager.cpp
        src/process_application.cpp
        src/process_application.hpp
        src/property.cpp
        src/context.cpp
        src/context.hpp
        src/remote_object.cpp
        src/image.cpp
        src/object_query.cpp
)

target_link_libraries(quite_client PRIVATE
    Boost::asio
    Boost::process
    asio-grpc::asio-grpc-stdexec
    nlohmann_json::nlohmann_json
    quite::protocol
PUBLIC
    quite::core
    STDEXEC::stdexec
)
target_compile_definitions(quite_client PUBLIC ASIO_TO_EXEC_USE_BOOST)
add_subdirectory(src/grpc_impl)
add_subdirectory(src/utils)
add_subdirectory(src/testing)
