set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES main.cpp mainwindow.cpp mainwindow.h mainwindow.ui)

qt_add_executable(WidgetsExample
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(WidgetsExample PRIVATE Qt6::Widgets quite::probe)

set_target_properties(
    WidgetsExample
    PROPERTIES
        ${BUNDLE_ID_OPTION} MACOSX_BUNDLE_BUNDLE_VERSION
        ${PROJECT_VERSION} MACOSX_BUNDLE_SHORT_VERSION_STRING
        ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} MACOSX_BUNDLE
        TRUE WIN32_EXECUTABLE
        TRUE
)
qt_finalize_executable(WidgetsExample)
