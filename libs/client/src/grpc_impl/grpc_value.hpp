// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <quite/proto/client/value_converter.hpp>
#include "grpc_probe_context.hpp"
namespace quite::client
{
class GrpcValueConverter final : public proto::IValueConverter
{
  public:
    explicit GrpcValueConverter(std::shared_ptr<GrpcProbeContext> probe_context);
    entt::meta_any from(ObjectReference ref) const override;

  private:
    std::weak_ptr<GrpcProbeContext> probe_context_;
};
} // namespace quite::client
