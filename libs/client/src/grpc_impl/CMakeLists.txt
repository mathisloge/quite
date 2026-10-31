# SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

target_sources(
    quite_client
    PRIVATE
        grpc_probe_context.hpp
        grpc_probe_context.cpp
        grpc_probe.hpp
        grpc_probe.cpp
        grpc_remote_object.hpp
        grpc_remote_object.cpp
        grpc_property.hpp
        grpc_property.cpp
        grpc_value.hpp
        grpc_value.cpp
)
