add_library(quite_manager)
add_library(quite::manager ALIAS quite_manager)
target_compile_features(quite_manager
    PUBLIC cxx_std_23
)
set_target_properties(quite_manager PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    VISIBILITY_INLINES_HIDDEN ON
)
generate_export_header(quite_manager EXPORT_FILE_NAME quite/quite_manager_export.hpp)

target_link_libraries(quite_manager
    PUBLIC
        quite::core
    PRIVATE
        Boost::process
        protobuf::libprotobuf
        asio-grpc::asio-grpc-stdexec
)

target_include_directories(quite_manager PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>"
)

target_sources(quite_manager
    PUBLIC
        FILE_SET headers
            TYPE HEADERS
            BASE_DIRS include
            FILES
                include/quite/manager/basic_process_manager.hpp
                include/quite/manager/process_manager.hpp
                include/quite/manager/process.hpp
                include/quite/manager/process_handle.hpp
                include/quite/manager/server.hpp
        FILE_SET export_config
            TYPE HEADERS
            BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
            FILES
                ${CMAKE_CURRENT_BINARY_DIR}/quite/quite_manager_export.hpp
    PRIVATE
        src/basic_process_manager.cpp
        src/process_manager.cpp
        src/process_impl.hpp
        src/process_impl.cpp
        src/noop_process.hpp
        src/noop_process.cpp
        src/process_handle.cpp
        src/remote_process_manager.cpp
        src/remote_process_manager.hpp
        src/server.cpp
)

asio_grpc_protobuf_generate(
    GENERATE_GRPC
    USAGE_REQUIREMENT PRIVATE
    TARGET quite_manager
    OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated"
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}"
    PROTOS
        "protocol/process_service.proto"
)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
