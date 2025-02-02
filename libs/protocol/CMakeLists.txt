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
)

target_link_libraries(quite_protocol PUBLIC protobuf::libprotobuf quite::core)

target_include_directories(quite_protocol
    PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>"
)

target_sources(quite_protocol
    PUBLIC
        FILE_SET headers
            TYPE HEADERS
            BASE_DIRS include
    FILES
        include/quite/proto/meta_converters.hpp
        FILE_SET export_config
        TYPE HEADERS
        BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/quite/quite_protocol_export.hpp
    PRIVATE
        src/meta_converters.cpp
)
