#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include <quite/remote_object.hpp>
#include "probe_handle.hpp"

namespace quite::grpc_impl
{
class GrpcRemoteObject final : public RemoteObject
{
  public:
    explicit GrpcRemoteObject(ObjectId id, ProbeServiceHandle probe_service_handle);

    exec::task<std::expected<ValueHandle, FindObjectErrorCode>> get_property(std::string_view property_name) override;

    exec::task<std::expected<void, FindObjectErrorCode>> mouse_action() override;

  private:
    ProbeServiceHandle probe_service_;
};
} // namespace quite::grpc
