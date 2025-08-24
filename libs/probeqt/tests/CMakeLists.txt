# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(test_probe_qt main.cpp)
add_sanitizers(test_probe_qt)
target_link_libraries(test_probe_qt PRIVATE Boost::ut probe_qt_impl)
add_test(NAME test_probe_qt COMMAND test_probe_qt)

target_sources(
    test_probe_qt
    PRIVATE
        test_object_tracker.cpp
        test_method_invoker.cpp
        test_property_collector.cpp
        test_value_containers.cpp
        test_probe_context.cpp
        test_qt_probe_handler.cpp
)
