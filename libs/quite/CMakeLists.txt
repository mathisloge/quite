add_library(quitelib SHARED)
add_library(quite::quite ALIAS quitelib)
set_target_properties(quitelib PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(quitelib)

target_compile_definitions(quitelib PUBLIC
    SPDLOG_ACTIVE_LEVEL=${log_level}
)

target_include_directories(quitelib PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    ${Stb_INCLUDE_DIR}
)

target_link_libraries(quitelib PRIVATE
    asio::asio
    asio-grpc::asio-grpc-stdexec
    nlohmann_json::nlohmann_json
    quite::protocol
    quite::logger
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
)
add_subdirectory(src/grpc_impl)
add_subdirectory(src/utils)
