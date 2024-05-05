#pragma once
#include <thread>
#include <agrpc/grpc_context.hpp>
#include <agrpc/grpc_executor.hpp>
#include <asio/io_context.hpp>
#include <quite/asio2exec.hpp>

namespace quite
{
class Context final
{
  public:
    ~Context();
    asio2exec::asio_context &asioContext();
    agrpc::GrpcContext &grpcContext();

  public:
    static Context &Instance();

  private:
    Context();

  private:
    asio2exec::asio_context asio_context_;
    agrpc::GrpcContext grpc_context_;
    std::jthread io_context_thread_;
    std::jthread grpc_context_thread_;
};
} // namespace quite
