find_package(Python REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(_quite binding.cpp)

target_link_libraries(_quite PUBLIC quite::quite)
target_compile_definitions(_quite PRIVATE VERSION_INFO=${PROJECT_VERSION})

install(TARGETS _quite DESTINATION quite)
