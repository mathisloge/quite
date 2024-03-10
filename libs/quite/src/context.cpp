#include "context.hpp"
#include <agrpc/asio_grpc.hpp>
#include <spdlog/spdlog.h>
namespace quite
{

Context::Context()
    : asio_workguard_{asio::make_work_guard(io_context_)}
    , grpc_workguard_{asio::make_work_guard(grpc_context_)}
    , io_context_thread_{[this]() {
        io_context_.run();
        spdlog::warn("exiting io_context");
    }}
    , grpc_context_thread_{[this]() {
        grpc_context_.run();
        spdlog::warn("exiting grpc_context");
    }}
{
}

Context::~Context()
{
    grpc_context_.stop();
    io_context_.stop();
}

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
