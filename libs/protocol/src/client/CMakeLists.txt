# SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

add_library(
    quite_protocol_client_impl
    OBJECT
    client.cpp
    configure_client_context.cpp
    configure_client_context.hpp
    grpc_manager.cpp
    grpc_manager.hpp
    meta_registry_impl.cpp
    meta_registry_impl.hpp
    mouse_injector_impl.cpp
    mouse_injector_impl.hpp
    probe_client_impl.cpp
    probe_client_impl.hpp
    probe_client.cpp
    probe_service_impl.cpp
    probe_service_impl.hpp
)
target_compile_features(quite_protocol_client_impl PUBLIC cxx_std_23)
set_target_properties(
    quite_protocol_client_impl
    PROPERTIES POSITION_INDEPENDENT_CODE ON
)
target_link_libraries(
    quite_protocol_client_impl
    PUBLIC quite::core quite_protocol_generated
    PRIVATE asio-grpc::asio-grpc-stdexec
)
target_include_directories(
    quite_protocol_client_impl
    PUBLIC
        "$<BUILD_INTERFACE:${quite_protocol_include_dir}>"
        "$<BUILD_INTERFACE:${quite_protocol_binary_dir}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>"
)

target_link_libraries(quite_protocol PRIVATE quite_protocol_client_impl)
