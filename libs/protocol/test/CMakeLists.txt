# SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

quite_add_test(
    NAME test_protocol
    SOURCES main.cpp test_server.cpp
    LIBRARIES quite::protocol fmt::fmt
    LABELS unit
    NO_GTEST_MAIN
)
