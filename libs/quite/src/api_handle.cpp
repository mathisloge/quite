#include "api_handle.hpp"
namespace quite
{

ApiHandle::ApiHandle(agrpc::GrpcContext &grpc_context)
    : object_client_{grpc_context}
{}

ApiHandle::~ApiHandle()
{}

ObjectClient &ApiHandle::object_client()
{
    return object_client_;
}
} // namespace quite
