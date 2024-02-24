cmake_minimum_required(VERSION 3.28)
project(quite CXX)

include(CTest)
include(GenerateExportHeader)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick REQUIRED)


add_subdirectory(libs)
add_subdirectory(test)
