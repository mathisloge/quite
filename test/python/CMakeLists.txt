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
        else
            echo \"Using libasan: \$libasan\"
            export ASAN_OPTIONS=detect_leaks=1:fast_unwind_on_malloc=0
            export LD_PRELOAD=\$libasan
        fi
        ${Python_EXECUTABLE} -m pytest --capture=tee-sys -vv ${CMAKE_CURRENT_SOURCE_DIR}
    "
)
set_tests_properties(
    PythonTests
    PROPERTIES
        ENVIRONMENT "WAYLAND_DISPLAY=$ENV{WAYLAND_DISPLAY}"
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
