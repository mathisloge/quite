# SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

quite_add_test(
    NAME test_probe_qt
    SOURCES
        main.cpp
        test_object_tracker.cpp
        test_method_invoker.cpp
        test_property_collector.cpp
        test_value_containers.cpp
        test_probe_context.cpp
        test_qt_probe_handler.cpp
    LIBRARIES probe_qt_impl
    LABELS qt
    NO_GTEST_MAIN
)
