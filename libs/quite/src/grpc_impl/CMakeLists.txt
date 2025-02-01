add_subdirectory(rpc)
add_subdirectory(meta_service)
target_sources(quite_client PRIVATE
    grpc_application.hpp
    grpc_application.cpp
    grpc_remote_object.hpp
    grpc_remote_object.cpp
    grpc_property.hpp
    grpc_property.cpp
    grpc_value.hpp
    grpc_value.cpp
    probe_client.hpp
    probe_client.cpp
)
