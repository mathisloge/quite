# SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

quite_add_test(
    NAME core_test
    SOURCES test_error.cpp
    LIBRARIES quite::core
    LABELS unit
)
