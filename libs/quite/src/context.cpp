#include "context.hpp"
#include <agrpc/asio_grpc.hpp>
namespace quite
{

Context::Context()
//: grpc_workguard_{asio::make_work_guard(grpc_context_)}
{
    asio_context_.start();
    grpc_context_thread_ = std::jthread{[grpc_context = grpc_context_]() {
        grpc_context->work_started();
        grpc_context->run();
    }};
}

Context::~Context()
{
    grpc_context_->stop();
    asio_context_.stop();
}

asio2exec::asio_context &Context::asioContext()
{
    return asio_context_;
}

std::shared_ptr<agrpc::GrpcContext> Context::grpcContext()
{
    return grpc_context_;
}

Context &Context::Instance()
{
    static Context context;
    return context;
}
} // namespace quite
