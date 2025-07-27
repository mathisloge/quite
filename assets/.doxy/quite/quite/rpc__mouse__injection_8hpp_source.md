

# File rpc\_mouse\_injection.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**probe**](dir_8a7b54f280cdd6b46c67f9938f379d86.md) **>** [**rpc\_mouse\_injection.hpp**](rpc__mouse__injection_8hpp.md)

[Go to the documentation of this file](rpc__mouse__injection_8hpp.md)


```C++
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
```


