

# File rpc\_snapshot.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**probe**](dir_8a7b54f280cdd6b46c67f9938f379d86.md) **>** [**rpc\_snapshot.hpp**](rpc__snapshot_8hpp.md)

[Go to the documentation of this file](rpc__snapshot_8hpp.md)


```C++
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
```


