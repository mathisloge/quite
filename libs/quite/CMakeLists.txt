add_library(quitelib)
add_library(quite::quite ALIAS quitelib)
set_target_properties(quitelib PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(quitelib)
configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/version.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/quite/version.hpp"
)

target_include_directories(quitelib
PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
PRIVATE
    ${Stb_INCLUDE_DIR}
)

target_link_libraries(quitelib PRIVATE
    asio::asio
    asio-grpc::asio-grpc-stdexec
    nlohmann_json::nlohmann_json
    quite::protocol
    quite::logger
PUBLIC
    quite::core
    STDEXEC::stdexec
)

target_sources(quitelib
    PRIVATE
        src/quite.cpp
        src/application.cpp
        src/process_application.cpp
        src/process_application.hpp
        src/process.cpp
        src/process.hpp
        src/property.cpp
        src/context.cpp
        src/context.hpp
        src/remote_object.cpp
        src/image.cpp
        src/object_query.cpp
        src/errors.cpp
)
add_subdirectory(src/grpc_impl)
add_subdirectory(src/utils)
add_subdirectory(src/testing)
add_subdirectory(src/meta)
