# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(test_application
    main.cpp
)
add_sanitizers(test_application)

qt_add_qml_module(test_application
    URI hello
    VERSION 1.0
    QML_FILES
        main.qml
    NO_RESOURCE_TARGET_PATH
    DEPENDENCIES QtQuick
)

target_link_libraries(
    test_application
    PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick quite::probe
)

file(
    GENERATE OUTPUT
    test_application_path.hpp
    INPUT test_application_path.in.hpp
    TARGET test_application
)
add_library(test_application_paths INTERFACE)
add_library(quite::test_application_paths ALIAS test_application_paths)
add_dependencies(test_application_paths tester)
target_include_directories(
    test_application_paths
    INTERFACE ${CMAKE_CURRENT_BINARY_DIR}
)
