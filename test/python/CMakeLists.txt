find_package(Python REQUIRED COMPONENTS Interpreter)
add_test(
    NAME PythonTests
    COMMAND
        /bin/bash -c
        "
        set -e
        # Locate libasan from Python bindings (or any ASan-linked binary)
        libasan=\$(ldd '$<TARGET_FILE:_quite>' | grep libasan | awk '{print \$3}')
        if [ -z \"\$libasan\" ]; then
            echo 'ERROR: libasan not found. Make sure target is built with -fsanitize=address'
            exit 1
        fi
        echo \"Using libasan: \$libasan\"
        export LD_PRELOAD=\$libasan
        export ASAN_OPTIONS=detect_leaks=0:allocator_may_return_null=1:handle_segv=0
        export LD_BIND_NOW=1  # Ensures symbols are resolved at load time (required by ASan)
        exec ${Python_EXECUTABLE} -m pytest --capture=tee-sys -vv ${CMAKE_CURRENT_SOURCE_DIR}
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
