# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

add_executable(test_manager_runnable runnable_exe.cpp)
add_sanitizers(test_manager_runnable)
target_link_libraries(test_manager_runnable PUBLIC CLI11::CLI11)
file(
    GENERATE OUTPUT
    runnable_path.hpp
    INPUT runnable_path.in.hpp
    TARGET test_manager_runnable
)
add_library(test_manager_runnable_if INTERFACE)
add_dependencies(test_manager_runnable_if test_manager_runnable)
target_include_directories(
    test_manager_runnable_if
    INTERFACE ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(test_manager main.cpp)
add_sanitizers(test_manager)
target_link_libraries(
    test_manager
    PRIVATE Boost::ut test_manager_runnable_if quite::manager CLI11::CLI11
)
add_test(NAME test_manager COMMAND test_manager)

target_sources(test_manager PRIVATE test_process_manager.cpp)
