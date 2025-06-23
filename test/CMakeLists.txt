add_subdirectory(simple_tester)

add_subdirectory(quite)
add_subdirectory(probeqt)
#add_subdirectory(protocol)

find_package(Python REQUIRED COMPONENTS Interpreter)
add_test(
    NAME PythonTests
    COMMAND ${Python_EXECUTABLE} -m pytest ${CMAKE_CURRENT_SOURCE_DIR}
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
