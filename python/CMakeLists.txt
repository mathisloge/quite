find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(_quite binding.cpp)
set_target_properties(_quite PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/quite)
target_link_libraries(_quite PRIVATE
    quite::quite
    fmt::fmt
)
target_compile_definitions(_quite PRIVATE VERSION_INFO=${PROJECT_VERSION})

add_custom_command(TARGET _quite POST_BUILD
    BYPRODUCTS quite/_quite.pyi quite/__init__.pyi
    COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=$<TARGET_FILE_DIR:_quite>/../ pybind11-stubgen -o ./ quite
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# enables loading when directly executing the module
file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/quite ${CMAKE_CURRENT_BINARY_DIR}/quite SYMBOLIC)

install(TARGETS _quite DESTINATION quite)
