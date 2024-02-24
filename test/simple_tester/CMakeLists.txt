qt_add_executable(tester
    main.cpp
)

qt_add_qml_module(tester
    URI hello
    QML_FILES
        main.qml
    NO_RESOURCE_TARGET_PATH
    DEPENDENCIES QtQuick
)

target_link_libraries(tester PUBLIC 
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    probe
)
