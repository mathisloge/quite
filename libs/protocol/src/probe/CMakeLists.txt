# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

target_sources(
    quite_protocol
    PRIVATE
        rpc_fetch_windows.hpp
        rpc_fetch_windows.cpp
        rpc_find_object.hpp
        rpc_find_object.cpp
        rpc_invoke_method.hpp
        rpc_invoke_method.cpp
        rpc_meta_find_type.hpp
        rpc_meta_find_type.cpp
        rpc_mouse_injection.hpp
        rpc_mouse_injection.cpp
        rpc_object_properties.hpp
        rpc_object_properties.cpp
        rpc_set_object_property.hpp
        rpc_set_object_property.cpp
        rpc_snapshot.hpp
        rpc_snapshot.cpp
        server.cpp
)
