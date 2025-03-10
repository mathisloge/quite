#pragma once
#include <quite/async_result.hpp>
#include <quite/proto/client/client.hpp>
#include <quite/proto/client/probe_client.hpp>
#include "basic_probe.hpp"
#include "grpc_value.hpp"
#include "quite/remote_object.hpp"
namespace quite::client
{
class GrpcProbe : public BasicProbe
{
  public:
    explicit GrpcProbe(manager::ApplicationManager::ApplicationHandle process, proto::Client &client);
    AsyncResult<std::shared_ptr<RemoteObject>> find_object(ObjectQuery query) override;
    AsyncResult<std::vector<std::shared_ptr<RemoteObject>>> get_views() override;
    meta::MetaRegistry &meta_registry() override;
    AsyncResult<void> wait_for_started(std::chrono::seconds timeout) override;

  private:
    std::shared_ptr<GrpcValueConverter> value_converter_{std::make_shared<GrpcValueConverter>()};
    std::shared_ptr<proto::ProbeClient> client_;
};
} // namespace quite::client
