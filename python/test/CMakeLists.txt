# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

find_package(Python REQUIRED COMPONENTS Interpreter)
add_test(
    NAME PythonTests
    COMMAND ${Python_EXECUTABLE} -m pytest -s ${CMAKE_CURRENT_SOURCE_DIR}
)
set_tests_properties(
    PythonTests
    PROPERTIES
        ENVIRONMENT
            "PYTHONPATH=$<TARGET_FILE_DIR:_quite>/../:${CMAKE_CURRENT_BINARY_DIR}"
)
file(
    GENERATE OUTPUT
    test_paths/__init__.py
    CONTENT
        [[
APP_PATH = "$<TARGET_FILE:tester>"
]]
)
