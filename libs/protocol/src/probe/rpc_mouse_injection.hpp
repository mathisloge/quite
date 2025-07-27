// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include "quite/injectors/mouse_injector.hpp"
#include "quite/service_handle.hpp"
namespace quite::proto
{
using MouseActionRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestMouseAction>;
struct MouseActionRpcHandler
{
    ServiceHandle<core::IMouseInjector> mouse_injector;
    exec::task<void> operator()(MouseActionRPC &, const MouseActionRPC::Request &) const;
};

agrpc::detail::RPCHandlerSender<MouseActionRPC, MouseActionRpcHandler> make_rpc_mouse_injection(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ServiceHandle<core::IMouseInjector> mouse_injector);
} // namespace quite::proto
