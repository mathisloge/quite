set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(tester
    main.cpp
)

qt_add_qml_module(tester
    URI hello
    QML_FILES
        main.qml
    SOURCES
        MyLogArea.hpp
        MyLogArea.cpp
    NO_RESOURCE_TARGET_PATH
    DEPENDENCIES QtQuick
)

target_link_libraries(tester PRIVATE 
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    spdlog::spdlog
    probe
)

file(GENERATE OUTPUT tester_app.hpp INPUT tester_app.in.hpp TARGET tester)
add_library(tester_app_if INTERFACE)
add_library(quite::tester_app ALIAS tester_app_if)
target_include_directories(tester_app_if INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
