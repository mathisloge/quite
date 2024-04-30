cmake_minimum_required(VERSION 3.28)
project(quite CXX)

include(CTest)
include(GenerateExportHeader)
Include(FetchContent)


set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Catch2 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(asio-grpc CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick REQUIRED)


add_subdirectory(libs)
add_subdirectory(test)
