# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

add_library(probe_qt_impl OBJECT)
target_compile_features(probe_qt_impl PUBLIC cxx_std_23)
target_include_directories(probe_qt_impl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(probe_qt_impl PROPERTIES AUTOMOC ON)

target_link_libraries(
    probe_qt_impl
    PUBLIC
        Qt6::CorePrivate
        Qt6::QuickPrivate
        Qt6::Widgets
        asio-grpc::asio-grpc-stdexec
        fmt::fmt
        EnTT::EnTT
        quite::protocol
        quite::core
        quite::probe
)

target_sources(
    probe_qt_impl
    PRIVATE
        object_tracker.cpp
        object_tracker.hpp
        property_collector.cpp
        property_collector.hpp
        qt_probe_handler.cpp
        qt_probe_handler.hpp
        value_converters.hpp
        value_converters.cpp
        probe_context.hpp
        probe_context.cpp
        method_invoker.cpp
        method_invoker.hpp
        qt_meta_registry.cpp
        qt_meta_registry.hpp
        meta_adapter.cpp
        meta_adapter.hpp
        qt_meta_type_accessor.hpp
        qt_meta_type_accessor.cpp
        meta_qt_containers.hpp
        injector/mouse_injector.hpp
        injector/mouse_injector.cpp
)
