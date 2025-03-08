#pragma once
#include <memory>
#include <thread>
#include <agrpc/grpc_context.hpp>
#include <quite/disable_copy_move.hpp>

namespace quite::proto
{
class GrpcManager final
{
  public:
    QUITE_DISABLE_COPY_MOVE(GrpcManager);
    GrpcManager();
    ~GrpcManager();

    std::shared_ptr<agrpc::GrpcContext> context();

  private:
    std::shared_ptr<agrpc::GrpcContext> grpc_context_;
    std::jthread grpc_thread_;
};
} // namespace quite::proto
