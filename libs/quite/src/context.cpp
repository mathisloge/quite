#include "context.hpp"
#include <agrpc/asio_grpc.hpp>
namespace quite
{

Context::Context()
    : io_context_thread_{[this] { io_context_.run(); }}
    , grpc_context_thread_{[this] { grpc_context_.run(); }}
{}
Context::~Context()
{}

asio::io_context &Context::ioContext()
{
    return io_context_;
}

agrpc::GrpcContext &Context::grpcContext()
{
    return grpc_context_;
}

Context &Context::Instance()
{
    static Context context;
    return context;
}
} // namespace quite
