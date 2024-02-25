add_library(probe SHARED)
add_library(quite::probe ALIAS probe)
set_target_properties(probe PROPERTIES 
    POSITION_INDEPENDENT_CODE ON
)
generate_export_header(probe)

target_include_directories(probe PUBLIC 
    "${CMAKE_CURRENT_BINARY_DIR}" 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(probe PRIVATE 
    Qt6::CorePrivate 
    Qt6::QuickPrivate
)

target_sources(probe
    PRIVATE
        src/object_tracker.cpp
        src/object_tracker.hpp
        src/probe.cpp
)
