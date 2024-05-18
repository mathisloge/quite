#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/proto/probe.grpc.pb.h>
namespace quite::grpc_impl
{
class ProbeClient final : public std::enable_shared_from_this<ProbeClient>
{
  public:
    ProbeClient(agrpc::GrpcContext &grpc_context);

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
