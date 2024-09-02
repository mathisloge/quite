#pragma once
#include "../probe_handle.hpp"
#include "quite/meta/meta_type_registry.hpp"

namespace quite::grpc_impl
{
class GrpcMetaTypeRegistry : public meta::MetaTypeRegistry
{
  public:
    GrpcMetaTypeRegistry(ProbeServiceHandle probe_service_handle);
    AsyncResult<meta::Type> resolve_type(meta::TypeId type_id) override;
    AsyncResult<meta::Type> resolve_type(std::string_view type_name) override;

  private:
    ProbeServiceHandle probe_service_handle_;
};
} // namespace quite::grpc_impl