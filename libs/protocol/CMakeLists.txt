set(proto_inc_dir "${CMAKE_CURRENT_LIST_DIR}/quite/proto")
asio_grpc_protobuf_generate(
    GENERATE_GRPC
    OUT_VAR "quite_protocol_proto_srcs"
    OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated"
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}"
    PROTOS 
        "${proto_inc_dir}/common.proto"
        "${proto_inc_dir}/probe.proto"
        "${proto_inc_dir}/keyboard.proto"
        "${proto_inc_dir}/mouse.proto"
        "${proto_inc_dir}/types.proto"
)

add_library(quite_protocol_proto STATIC)
add_library(quite::protocol ALIAS quite_protocol_proto)
target_sources(quite_protocol_proto PRIVATE ${quite_protocol_proto_srcs})
target_link_libraries(quite_protocol_proto PUBLIC protobuf::libprotobuf)

target_include_directories(quite_protocol_proto 
    PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>"
)
