# SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

quite_add_test(
    NAME test_protocol
    SOURCES
        main.cpp
        test_server.cpp
        test_server_with_fake_handler.cpp
        client/test_probe_service_impl.cpp
        client/test_meta_registry_impl.cpp
        client/test_mouse_injector_impl.cpp
    LIBRARIES quite::protocol quite_protocol_client_impl asio-grpc::asio-grpc-stdexec fmt::fmt
    LABELS unit
    NO_GTEST_MAIN
)
target_include_directories(
    test_protocol
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src/client"
)
