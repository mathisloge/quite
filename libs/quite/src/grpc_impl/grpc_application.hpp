#pragma once
#include "../context.hpp"
#include "meta_service/grpc_meta_type_registry.hpp"
#include "probe_handle.hpp"
#include "quite/application.hpp"
#include "quite/remote_object.hpp"
namespace quite::grpc_impl
{
class GrpcApplication : public Application
{
  public:
    explicit GrpcApplication(Context &context);
    AsyncResult<std::shared_ptr<RemoteObject>> find_object(const ObjectQuery &query) override;
    AsyncResult<std::vector<std::shared_ptr<RemoteObject>>> get_views() override;
    AsyncResult<void> exit() override;
    meta::MetaRegistry &meta_registry() override;

  private:
    ProbeServiceHandle probe_handle_;
    GrpcMetaTypeRegistry meta_type_registry_;
};
} // namespace quite::grpc_impl
