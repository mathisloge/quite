add_subdirectory(simple_tester)

add_subdirectory(quite)
add_subdirectory(probeqt)
#add_subdirectory(protocol)

find_package(Python REQUIRED COMPONENTS Interpreter)
add_test(
    NAME PythonTests
    COMMAND
        /bin/bash -c
        "
        set -e
        target='$<TARGET_FILE:_quite>'
        if [ ! -f \"$target\" ]; then
            echo 'Target binary not found: ' \"$target\"
            exit 1
        fi
        libasan=\$(ldd \"$target\" | grep libasan | awk '{print \$3}')
        if [ -z \"\$libasan\" ]; then
            echo 'libasan not found; running without LD_PRELOAD'
            LD_PRELOAD= PYTHONPATH=\"$<TARGET_FILE_DIR:_quite>/../:${CMAKE_CURRENT_BINARY_DIR}\" \
                ${Python_EXECUTABLE} -m pytest ${CMAKE_CURRENT_SOURCE_DIR}
        else
            echo \"Using libasan: \$libasan\"
            LD_PRELOAD=\$libasan PYTHONPATH=\"$<TARGET_FILE_DIR:_quite>/../:${CMAKE_CURRENT_BINARY_DIR}\" \
                ${Python_EXECUTABLE} -m pytest ${CMAKE_CURRENT_SOURCE_DIR}
        fi
    "
)

file(
    GENERATE OUTPUT
    test_paths/__init__.py
    CONTENT
        [[
APP_PATH = "$<TARGET_FILE:tester>"
]]
)
