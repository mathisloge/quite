include(Catch)

add_subdirectory(simple_tester)

add_subdirectory(quite)

find_package(Python REQUIRED COMPONENTS Interpreter)
add_test(NAME PythonTests
    COMMAND ${Python_EXECUTABLE} -m pytest ${CMAKE_CURRENT_SOURCE_DIR}
)
set_tests_properties(PythonTests PROPERTIES
    ENVIRONMENT "PYTHONPATH=$<TARGET_FILE_DIR:_quite>/../"
)
