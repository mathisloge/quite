#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include <quite/remote_object.hpp>
#include "probe_handle.hpp"

namespace quite::grpc_impl
{
class GrpcRemoteObject final : public std::enable_shared_from_this<GrpcRemoteObject>, public RemoteObject
{
  public:
    explicit GrpcRemoteObject(ObjectId id, meta::TypeId type_id, ProbeServiceHandle probe_service_handle);

    meta::TypeId type_id() const override;

    AsyncResult<std::unordered_map<std::string, PropertyPtr>> fetch_properties(
        std::span<const std::string> properties) override;

    AsyncResult<PropertyPtr> property(std::string property_name) override;

    AsyncResult<void> mouse_action() override;

    AsyncResult<Image> take_snapshot() override;

    AsyncResult<void> invoke_method(std::string method_name) override;

  private:
    ProbeServiceHandle probe_service_;
    meta::TypeId type_id_;
};
} // namespace quite::grpc_impl
