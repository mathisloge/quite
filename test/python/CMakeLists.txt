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
            WAYLAND_DISPLAY=$ENV{WAYLAND_DISPLAY} LD_PRELOAD= PYTHONPATH=\"$<TARGET_FILE_DIR:_quite>/../:${CMAKE_CURRENT_BINARY_DIR}\" \
                ${Python_EXECUTABLE} -m pytest --capture=tee-sys -vv ${CMAKE_CURRENT_SOURCE_DIR}
        else
            echo \"Using libasan: \$libasan\"
            WAYLAND_DISPLAY=$ENV{WAYLAND_DISPLAY} ASAN_OPTIONS=\"detect_leaks=0:allocator_may_return_null=1:handle_segv=0\" LD_PRELOAD=\$libasan PYTHONPATH=\"$<TARGET_FILE_DIR:_quite>/../:${CMAKE_CURRENT_BINARY_DIR}\" \
                ${Python_EXECUTABLE} -m pytest --capture=tee-sys -vv ${CMAKE_CURRENT_SOURCE_DIR}
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
