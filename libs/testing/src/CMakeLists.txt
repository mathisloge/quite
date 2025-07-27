# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

target_sources(
    quite_test
    PRIVATE
        probe_manager.cpp
        probe.cpp
        exceptions.cpp
        property.cpp
        remote_object.cpp
        expect_screenshot.cpp
        expect_screenshot.hpp
        expect.cpp
)
