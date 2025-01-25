#pragma once
#include <quite/meta/meta_registry.hpp>
#include "../probe_handle.hpp"

namespace quite::grpc_impl
{
class GrpcMetaTypeRegistry : public meta::MetaRegistry
{
  public:
    GrpcMetaTypeRegistry(ProbeServiceHandle probe_service_handle);
    AsyncResult<meta::Type> lookup_type(meta::TypeId type_id) override;

  private:
    ProbeServiceHandle probe_service_handle_;
};
} // namespace quite::grpc_impl
