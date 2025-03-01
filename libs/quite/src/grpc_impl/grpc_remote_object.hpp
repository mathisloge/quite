#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/remote_object.hpp>
#include <quite/value/object_id.hpp>
#include "quite/proto/client/probe_client.hpp"

namespace quite
{
class GrpcRemoteObject final : public std::enable_shared_from_this<GrpcRemoteObject>, public RemoteObject
{
  public:
    explicit GrpcRemoteObject(ObjectReference reference, std::shared_ptr<proto::ProbeClient> client);

    meta::TypeId type_id() const override;

    AsyncResult<std::unordered_map<std::string, PropertyPtr>> fetch_properties(
        std::vector<std::string> properties) override;

    AsyncResult<PropertyPtr> property(std::string property_name) override;
    AsyncResult<Value> fetch_property(std::string property_name);

    AsyncResult<void> mouse_action() override;

    AsyncResult<Image> take_snapshot() override;

    AsyncResult<void> invoke_method(std::string method_name) override;

  private:
    std::shared_ptr<proto::ProbeClient> client_;
    meta::TypeId type_id_;
};
} // namespace quite
