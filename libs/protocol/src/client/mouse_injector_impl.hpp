// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/injectors/mouse_injector.hpp>
#include "quite/proto/probe.grpc.pb.h"

namespace quite::proto
{
class MouseInjectorImpl final : public core::IMouseInjector
{
  public:
    explicit MouseInjectorImpl(std::shared_ptr<agrpc::GrpcContext> grpc_context,
                               ProbeService::Stub &probe_service_stub);
    AsyncResult<void> single_action(ObjectId target_id, core::MouseAction action) override;

  private:
    std::shared_ptr<agrpc::GrpcContext> grpc_context_;
    ProbeService::Stub &probe_service_stub_;
};
} // namespace quite::proto
