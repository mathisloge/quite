# SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

quite_add_test(
    NAME client_test
    SOURCES test_dump_properties.cpp test_verification_point.cpp
    LIBRARIES quite::client nlohmann_json::nlohmann_json
    LABELS unit
)
