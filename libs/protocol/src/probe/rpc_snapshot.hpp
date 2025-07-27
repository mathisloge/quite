// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include "probe_handler_handle.hpp"

namespace quite::proto
{
using RpcSnapshot = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestCreateScreenshot>;
struct SnapshotRpcHandler
{
    ProbeHandlerHandle probe_handler;
    exec::task<void> operator()(RpcSnapshot &rpc, const RpcSnapshot::Request &request) const;
};

agrpc::detail::RPCHandlerSender<RpcSnapshot, SnapshotRpcHandler> make_rpc_snapshot(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ProbeHandlerHandle probe_handler);
} // namespace quite::proto
