# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

configure_file(bdd_features.in.hpp bdd_features.hpp @ONLY)
add_library(test_bdd_paths INTERFACE)
add_library(quite::test_bdd_paths ALIAS test_bdd_paths)
target_include_directories(test_bdd_paths INTERFACE ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(test_application)
add_subdirectory(cpp_test)
add_subdirectory(python_test)
