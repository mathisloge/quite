#pragma once
#include "probe_handle.hpp"
#include "quite/application.hpp"
#include "quite/remote_object.hpp"
#include "../context.hpp"
namespace quite::grpc_impl
{
class GrpcApplication : public Application
{
  public:
  explicit GrpcApplication(Context &context);
    AsyncResult<std::shared_ptr<RemoteObject>> find_object(std::string_view object_name) override;
    AsyncResult<std::vector<std::shared_ptr<RemoteObject>>> get_views() override;

  private:
    ProbeServiceHandle probe_handle_;
};
} // namespace quite::grpc_impl
