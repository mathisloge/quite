# SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

set(proto_inc_dir "${CMAKE_CURRENT_LIST_DIR}/quite/proto")
set(quite_protocol_binary_dir "${CMAKE_CURRENT_BINARY_DIR}")
set(quite_protocol_include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(quite_protocol_generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Generated protobuf/grpc sources live in their own object library so that both
# quite_protocol and quite_protocol_client_impl (an internal dependency OF quite_protocol,
# see src/client/CMakeLists.txt) can depend on them without creating a build-graph cycle.
add_library(quite_protocol_generated OBJECT)
add_sanitizers(quite_protocol_generated)
target_compile_features(quite_protocol_generated PUBLIC cxx_std_23)
set_target_properties(
    quite_protocol_generated
    PROPERTIES POSITION_INDEPENDENT_CODE ON
)
asio_grpc_protobuf_generate(
    GENERATE_GRPC
    GENERATE_MOCK_CODE
    USAGE_REQUIREMENT PUBLIC
    TARGET quite_protocol_generated
    OUT_DIR "${quite_protocol_generated_dir}"
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
target_link_libraries(
    quite_protocol_generated
    PUBLIC protobuf::libprotobuf gRPC::grpc gRPC::grpc++
)

add_library(quite_protocol)
add_library(quite::protocol ALIAS quite_protocol)
add_sanitizers(quite_protocol)
target_compile_features(quite_protocol PUBLIC cxx_std_23)
set_target_properties(
    quite_protocol
    PROPERTIES POSITION_INDEPENDENT_CODE ON VISIBILITY_INLINES_HIDDEN 1
)
generate_export_header(
    quite_protocol
    EXPORT_FILE_NAME quite/quite_protocol_export.hpp
)

target_link_libraries(
    quite_protocol
    PUBLIC quite::core
    PRIVATE quite_protocol_generated asio-grpc::asio-grpc-stdexec
)

target_include_directories(
    quite_protocol
    PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
)

target_sources(
    quite_protocol
    PUBLIC
        FILE_SET headers
            TYPE HEADERS
            BASE_DIRS include
            FILES
                include/quite/proto/probe/server.hpp
                include/quite/proto/probe/probe_handler.hpp
                include/quite/proto/client/probe_client.hpp
                include/quite/proto/client/probe_service.hpp
                include/quite/proto/client/client.hpp
                include/quite/proto/client/value_converter.hpp
        FILE_SET export_config
            TYPE HEADERS
            BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
            FILES ${CMAKE_CURRENT_BINARY_DIR}/quite/quite_protocol_export.hpp
    PRIVATE
        src/meta_converters.cpp
        src/meta_converters.hpp
        src/value.cpp
        src/value.hpp
        src/error_helper.cpp
        src/error_helper.hpp
)

add_subdirectory(src/probe)
add_subdirectory(src/client)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
