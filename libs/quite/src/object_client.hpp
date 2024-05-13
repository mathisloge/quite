#pragma once
#include <expected>
#include <agrpc/grpc_context.hpp>
#include <quite/basic_remote_object.hpp>
#include <quite/proto/probe.grpc.pb.h>
namespace quite
{
class ObjectClient final : public std::enable_shared_from_this<ObjectClient>
{
  public:
    ObjectClient(agrpc::GrpcContext &grpc_context);

    agrpc::GrpcContext &context()
    {
        return grpc_context_;
    }
    
    proto::ProbeService::Stub &stub()
    {
        return stub_;
    }

  private:
    agrpc::GrpcContext &grpc_context_;
    proto::ProbeService::Stub stub_;
};
} // namespace quite
