set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_library(probeqt STATIC)
add_library(quite::probeqt ALIAS probeqt)
set_target_properties(probeqt PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(probeqt)

target_include_directories(probeqt PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(probeqt PUBLIC
    Qt6::CorePrivate
    Qt6::QuickPrivate
    Qt6::Widgets
    asio-grpc::asio-grpc-stdexec
    fmt::fmt
    EnTT::EnTT
    quite::protocol
    quite::core
)

target_sources(probeqt
    PRIVATE
        object_tracker.cpp
        object_tracker.hpp
        property_collector.cpp
        property_collector.hpp
        snapshot_handler.cpp
        snapshot_handler.hpp
        value_converters.hpp
        value_converters.cpp
        proto_converters.cpp
        proto_converters.hpp
        probe_context.hpp
        probe_context.cpp
        method_invoker.cpp
        method_invoker.hpp
        qt_meta_registry.cpp
        qt_meta_registry.hpp
        meta_adapter.cpp
        meta_adapter.hpp
        qt_meta_type_accessor.hpp
        qt_meta_type_accessor.cpp
        meta_qt_containers.hpp
)
add_subdirectory(injector)
add_subdirectory(rpc)

#target_compile_options(probeqt PRIVATE -fno-omit-frame-pointer -fsanitize=address)
#target_link_options(probeqt PRIVATE -fno-omit-frame-pointer -fsanitize=address)
