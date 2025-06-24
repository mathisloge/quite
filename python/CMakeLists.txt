pybind11_add_module(_quite binding.cpp)
add_sanitizers(_quite)
set_target_properties(
    _quite
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/quite
)
target_link_libraries(_quite PRIVATE quite::test)
target_compile_definitions(_quite PRIVATE VERSION_INFO=${PROJECT_VERSION})

add_custom_command(
    TARGET _quite
    POST_BUILD
    BYPRODUCTS quite/_quite.pyi quite/__init__.pyi
    COMMAND
        ${CMAKE_COMMAND} -E env bash -c
        "libasan=\$(ldd \"$<TARGET_FILE:_quite>\" | grep libasan | awk '{print \$3}');echo \"Detected libasan: \$libasan\";LD_PRELOAD=\$libasan PYTHONPATH=\"$<TARGET_FILE_DIR:_quite>/..\" stubgen -o ./ -p quite --include-docstrings || (exit 0)"
    VERBATIM
)

# enables loading when directly executing the module
file(
    CREATE_LINK
        ${CMAKE_CURRENT_SOURCE_DIR}/quite
        ${CMAKE_CURRENT_BINARY_DIR}/quite
    SYMBOLIC
)

install(TARGETS _quite DESTINATION quite)
