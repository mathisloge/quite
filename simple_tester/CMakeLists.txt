# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(tester
    main.cpp
)
add_sanitizers(tester)

qt_add_qml_module(tester
    URI hello
    VERSION 1.0
    QML_FILES
        main.qml
    SOURCES
        MyLogArea.hpp
        MyLogArea.cpp
        MyCustomType.hpp
        MyCustomType.cpp
    NO_RESOURCE_TARGET_PATH
    DEPENDENCIES QtQuick
)

target_link_libraries(
    tester
    PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick quite::probe_qt
)

file(GENERATE OUTPUT tester_app.hpp INPUT tester_app.in.hpp TARGET tester)
add_library(tester_app_if INTERFACE)
add_library(quite::tester_app ALIAS tester_app_if)
add_dependencies(tester_app_if tester)
target_include_directories(tester_app_if INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
