

# File rpc\_meta\_find\_type.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**probe**](dir_8a7b54f280cdd6b46c67f9938f379d86.md) **>** [**rpc\_meta\_find\_type.hpp**](rpc__meta__find__type_8hpp.md)

[Go to the documentation of this file](rpc__meta__find__type_8hpp.md)


```C++
#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/meta/meta_registry.hpp>
#include <quite/proto/meta_service.grpc.pb.h>
#include <quite/service_handle.hpp>

namespace quite::proto
{
using FindTypeRPC = agrpc::ServerRPC<&quite::proto::MetaService::AsyncService::RequestFindType>;
struct GetMetaObjectRpcHandler
{
    ServiceHandle<meta::MetaRegistry> meta_registry;
    exec::task<void> operator()(FindTypeRPC &rpc, const FindTypeRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<FindTypeRPC, GetMetaObjectRpcHandler> make_rpc_meta_find_type(
    agrpc::GrpcContext &grpc_context,
    quite::proto::MetaService::AsyncService &service,
    ServiceHandle<meta::MetaRegistry> meta_registry);
} // namespace quite::proto
```


