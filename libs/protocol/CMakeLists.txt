add_library(protocol STATIC)
add_library(quite::protocol ALIAS protocol)

target_include_directories(protocol PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(protocol PRIVATE 
    uvw::uvw
)

target_sources(protocol
    PRIVATE
        src/protocol.cpp
)
