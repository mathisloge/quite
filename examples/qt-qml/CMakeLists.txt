find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appqt-qml
    main.cpp
)

qt_add_qml_module(appqt-qml
    URI "Example.Qml"
    VERSION 1.0
    QML_FILES
        Main.qml
)

set_target_properties(appqt-qml PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appqt-qml
    PRIVATE Qt6::Quick quite::probe
)
