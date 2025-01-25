#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/proto/meta_service.grpc.pb.h>
#include <quite/proto/probe.grpc.pb.h>
namespace quite::grpc_impl
{
class ProbeClient final : public std::enable_shared_from_this<ProbeClient>
{
  public:
    ProbeClient(std::shared_ptr<agrpc::GrpcContext> grpc_context);

    agrpc::GrpcContext &context()
    {
        return *grpc_context_;
    }

    proto::ProbeService::Stub &stub()
    {
        return stub_;
    }

    proto::MetaService::Stub &meta_service_stub()
    {
        return meta_service_stub_;
    }

  private:
    std::shared_ptr<agrpc::GrpcContext> grpc_context_;
    std::shared_ptr<grpc::Channel> grpc_channel_;
    proto::ProbeService::Stub stub_;
    proto::MetaService::Stub meta_service_stub_;
};
} // namespace quite::grpc_impl
