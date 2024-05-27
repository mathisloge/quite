#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include <quite/remote_object.hpp>
#include "probe_handle.hpp"

namespace quite::grpc_impl
{
class GrpcRemoteObject final : public RemoteObject, public std::enable_shared_from_this<GrpcRemoteObject>
{
  public:
    explicit GrpcRemoteObject(ObjectId id, ProbeServiceHandle probe_service_handle);

    AsyncResult<std::unordered_map<std::string, std::unique_ptr<Value>>> fetch_properties(
        const std::vector<std::string_view> &properties) override;

    AsyncResult<void> mouse_action() override;

    AsyncResult<Image> take_snapshot() override;

  private:
    ProbeServiceHandle probe_service_;
};
} // namespace quite::grpc_impl
