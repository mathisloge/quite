#include "grpc_manager.hpp"
namespace quite::proto
{
GrpcManager::GrpcManager()
    : grpc_context_{std::make_shared<agrpc::GrpcContext>()}
    , grpc_thread_{[grpc_context = grpc_context_]() {
        grpc_context->work_started();
        grpc_context->run();
    }}
{}

GrpcManager::~GrpcManager() = default;

std::shared_ptr<agrpc::GrpcContext> GrpcManager::context()
{
    return grpc_context_;
}
} // namespace quite::proto
