

# File rpc\_object\_properties.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**probe**](dir_8a7b54f280cdd6b46c67f9938f379d86.md) **>** [**rpc\_object\_properties.hpp**](rpc__object__properties_8hpp.md)

[Go to the documentation of this file](rpc__object__properties_8hpp.md)


```C++
#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include "probe/probe_handler_handle.hpp"
#include "quite/value/value_registry.hpp"

namespace quite::proto
{
using GetObjectPropertiesRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestGetObjectProperties>;
struct GetObjectPropertiesRpcHandler
{
    ProbeHandlerHandle probe_handler;
    ServiceHandle<ValueRegistry> value_registry;
    exec::task<void> operator()(GetObjectPropertiesRPC &rpc, const GetObjectPropertiesRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<GetObjectPropertiesRPC, GetObjectPropertiesRpcHandler> make_rpc_fetch_object_properties(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ProbeHandlerHandle probe_handler,
    ServiceHandle<ValueRegistry> value_registry);
} // namespace quite::proto
```


