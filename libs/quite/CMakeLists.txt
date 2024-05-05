add_library(quitelib SHARED)
add_library(quite::quite ALIAS quitelib)
set_target_properties(quitelib PROPERTIES 
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(quitelib)

target_include_directories(quitelib PUBLIC 
    "${CMAKE_CURRENT_BINARY_DIR}" 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(quitelib PRIVATE 
    asio::asio
    asio-grpc::asio-grpc-stdexec
    spdlog::spdlog
    quite::protocol
)

target_sources(quitelib
    PRIVATE
        src/quite.cpp
        src/application.cpp
        src/process_application.cpp
        src/process_application.hpp
        src/process.cpp
        src/process.hpp
        src/object_client.cpp
        src/object_client.hpp
        src/context.cpp
        src/context.hpp
        src/remote_object.cpp
        src/remote_object.hpp
)
