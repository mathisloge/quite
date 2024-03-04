#include "quite/object_server.hpp"
#include <agrpc/asio_grpc.hpp>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

namespace quite::proto
{

ObjectServer::ObjectServer()
{
    grpc::ServerBuilder builder;
    agrpc::GrpcContext grpc_context{builder.AddCompletionQueue()};
    builder.AddListeningPort(host, grpc::InsecureServerCredentials());
    builder.RegisterService(&service_);
    server_ = builder.BuildAndStart();
}

ObjectServer::~ObjectServer() = default;

} // namespace quite::proto
