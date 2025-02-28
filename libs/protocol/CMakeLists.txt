set(proto_inc_dir "${CMAKE_CURRENT_LIST_DIR}/quite/proto")

add_library(quite_protocol STATIC)
add_library(quite::protocol ALIAS quite_protocol)
set_target_properties(quite_protocol PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(quite_protocol EXPORT_FILE_NAME quite/quite_protocol_export.hpp)
asio_grpc_protobuf_generate(
    GENERATE_GRPC
    USAGE_REQUIREMENT PUBLIC
    TARGET quite_protocol
    OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated"
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}"
    PROTOS
        "${proto_inc_dir}/meta.proto"
        "${proto_inc_dir}/meta_service.proto"
        "${proto_inc_dir}/common.proto"
        "${proto_inc_dir}/probe.proto"
        "${proto_inc_dir}/keyboard.proto"
        "${proto_inc_dir}/mouse.proto"
        "${proto_inc_dir}/types.proto"
        "${proto_inc_dir}/methods.proto"
        "${proto_inc_dir}/health.proto"
)

target_link_libraries(quite_protocol
    PUBLIC
        quite::core
        # todo: move to private
        protobuf::libprotobuf
    PRIVATE
        asio-grpc::asio-grpc-stdexec
)

target_include_directories(quite_protocol
    PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>"
    PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
)

target_sources(quite_protocol
    PUBLIC
        FILE_SET headers
            TYPE HEADERS
            BASE_DIRS include
    FILES
        include/quite/proto/meta_converters.hpp
        include/quite/proto/value.hpp
        include/quite/proto/probe/server.hpp
        include/quite/proto/probe/probe_handler.hpp
        include/quite/proto/probe/dependencies.hpp
    FILE_SET export_config
        TYPE HEADERS
        BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/quite/quite_protocol_export.hpp
    PRIVATE
        src/meta_converters.cpp
        src/value.cpp
        src/error_helper.cpp
        src/error_helper.hpp
)

add_subdirectory(src/probe)
