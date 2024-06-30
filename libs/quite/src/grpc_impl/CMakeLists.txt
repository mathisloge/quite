add_subdirectory(rpc)
target_sources(quitelib PRIVATE
    grpc_application.hpp
    grpc_application.cpp
    grpc_remote_object.hpp
    grpc_remote_object.cpp
    grpc_property.hpp
    grpc_property.cpp
    probe_client.hpp
    probe_client.cpp
)
