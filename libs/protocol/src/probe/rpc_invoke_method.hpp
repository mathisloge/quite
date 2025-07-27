// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include "probe_handler_handle.hpp"
#include "quite/value/value_registry.hpp"

namespace quite::proto
{
using InvokeMethodRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestInvokeMethod>;
struct InvokeMethodRpcHandler
{
    ProbeHandlerHandle probe_handler;
    ServiceHandle<ValueRegistry> value_registry;
    exec::task<void> operator()(InvokeMethodRPC &, const InvokeMethodRPC::Request &) const;
};

agrpc::detail::RPCHandlerSender<InvokeMethodRPC, InvokeMethodRpcHandler> make_rpc_invoke_method(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ProbeHandlerHandle probe_handler,
    ServiceHandle<ValueRegistry> value_registry);
} // namespace quite::proto
