#pragma once
#include <thread>
#include <agrpc/grpc_context.hpp>
#include <agrpc/grpc_executor.hpp>
#include <asio/io_context.hpp>

namespace quite
{
class Context final
{
  public:
    ~Context();
    asio::io_context &ioContext();
    agrpc::GrpcContext &grpcContext();

  public:
    static Context &Instance();

  private:
    Context();

  private:
    asio::io_context io_context_;
    agrpc::GrpcContext grpc_context_;
    asio::executor_work_guard<asio::io_context::executor_type> asio_workguard_;
    asio::executor_work_guard<agrpc::GrpcExecutor> grpc_workguard_;
    std::jthread io_context_thread_;
    std::jthread grpc_context_thread_;
};
} // namespace quite
