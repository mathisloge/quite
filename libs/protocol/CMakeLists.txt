add_subdirectory(proto)

add_library(protocol STATIC)
add_library(quite::protocol ALIAS protocol)

target_include_directories(protocol PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(protocol 
    PUBLIC
        spdlog::spdlog
        asio::asio
        asio-grpc::asio-grpc-standalone-asio
        quite::protocol_proto
)

target_sources(protocol
    PRIVATE
        src/object_service.cpp
        src/basic_object_client.cpp
)
