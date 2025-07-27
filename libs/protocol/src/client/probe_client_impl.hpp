// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <agrpc/grpc_context.hpp>
#include <grpcpp/channel.h>
#include "grpc_manager.hpp"
#include "meta_registry_impl.hpp"
#include "mouse_injector_impl.hpp"
#include "probe_service_impl.hpp"
#include "quite/proto/client/probe_client.hpp"
#include "quite/proto/client/value_converter.hpp"
#include "quite/proto/meta_service.grpc.pb.h"
#include "quite/proto/probe.grpc.pb.h"
namespace quite::proto
{
class ProbeClientImpl final : public ProbeClient
{
  public:
    ProbeClientImpl(GrpcManager &grpc_manager,
                    std::string connection_url,
                    std::shared_ptr<IValueConverter> value_converter);
    AsyncResult<void> wait_for_connected(std::chrono::seconds timeout) override;
    IProbeService &probe_service() override;
    core::IMouseInjector &mouse_injector() override;
    meta::MetaRegistry &meta_registry() override;

  private:
    std::shared_ptr<agrpc::GrpcContext> grpc_context_;
    std::shared_ptr<grpc::Channel> grpc_channel_;
    std::shared_ptr<IValueConverter> value_converter_;
    ProbeService::Stub probe_service_stub_{grpc_channel_};
    MetaService::Stub meta_service_stub_{grpc_channel_};
    ProbeServiceImpl probe_service_{grpc_context_, probe_service_stub_, value_converter_};
    MetaRegistryImpl meta_registry_{grpc_context_, meta_service_stub_};
    MouseInjectorImpl mouse_injector_{grpc_context_, probe_service_stub_};
};
} // namespace quite::proto
