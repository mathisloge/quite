# SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

quite_add_test(
    NAME test_testing
    SOURCES test_value_convert.cpp test_throw_unexpected.cpp test_property.cpp
    LIBRARIES quite::test
    LABELS unit
)
target_compile_features(test_testing PUBLIC cxx_std_23)
target_include_directories(
    test_testing
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src"
)
