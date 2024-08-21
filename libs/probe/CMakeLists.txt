set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_library(probe)
add_library(quite::probe ALIAS probe)
set_target_properties(probe PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(probe)

target_include_directories(probe PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(probe PRIVATE
    Qt6::CorePrivate
    Qt6::QuickPrivate
    Qt6::Widgets
    fmt::fmt
    quite::protocol
    quite::logger
    asio-grpc::asio-grpc-stdexec
    EnTT::EnTT
)

target_sources(probe
    PRIVATE
        src/object_tracker.cpp
        src/object_tracker.hpp
        src/probe.cpp
        src/property_collector.cpp
        src/property_collector.hpp
        src/snapshot.hpp
        src/snapshot.cpp
        src/value_converters.hpp
        src/value_converters.cpp
)
add_subdirectory(src/injector)
add_subdirectory(src/rpc)


install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/probe_export.h" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
