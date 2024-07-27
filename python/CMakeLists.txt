find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(_quite binding.cpp)
set_target_properties(_quite PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/quite)
target_link_libraries(_quite PUBLIC quite::quite)
target_compile_definitions(_quite PRIVATE VERSION_INFO=${PROJECT_VERSION})
# enables loading when directly executing the module
file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/quite ${CMAKE_CURRENT_BINARY_DIR}/quite SYMBOLIC)

install(TARGETS _quite DESTINATION quite)
