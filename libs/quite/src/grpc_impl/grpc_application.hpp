#pragma once
#include <quite/async_result.hpp>
#include <quite/proto/client/probe_client.hpp>
#include "../context.hpp"
#include "quite/application.hpp"
#include "quite/remote_object.hpp"
namespace quite
{
class GrpcApplication : public Application
{
  public:
    explicit GrpcApplication(Context &context);
    AsyncResult<std::shared_ptr<RemoteObject>> find_object(ObjectQuery query) override;
    AsyncResult<std::vector<std::shared_ptr<RemoteObject>>> get_views() override;
    meta::MetaRegistry &meta_registry() override;
    AsyncResult<void> wait_for_started(std::chrono::seconds timeout) override;
    AsyncResult<void> exit() override;

  private:
    std::shared_ptr<proto::ProbeClient> client_;
};
} // namespace quite
