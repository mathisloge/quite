// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/meta/meta_registry.hpp>
#include "quite/proto/meta_service.grpc.pb.h"

namespace quite::proto
{
class MetaRegistryImpl : public meta::MetaRegistry
{
  public:
    explicit MetaRegistryImpl(std::shared_ptr<agrpc::GrpcContext> grpc_context, MetaService::Stub &meta_service_stub);
    AsyncResult<meta::Type> lookup_type(meta::TypeId type_id) override;

  private:
    std::shared_ptr<agrpc::GrpcContext> grpc_context_;
    MetaService::Stub &meta_service_stub_;
};
} // namespace quite::proto
