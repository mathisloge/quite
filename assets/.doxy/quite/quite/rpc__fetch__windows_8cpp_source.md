

# File rpc\_fetch\_windows.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**probe**](dir_8a7b54f280cdd6b46c67f9938f379d86.md) **>** [**rpc\_fetch\_windows.cpp**](rpc__fetch__windows_8cpp.md)

[Go to the documentation of this file](rpc__fetch__windows_8cpp.md)


```C++
#include "rpc_fetch_windows.hpp"
#include <agrpc/register_sender_rpc_handler.hpp>
#include "error_helper.hpp"
#include "quite/proto/probe/probe_handler.hpp"

namespace quite::proto
{
exec::task<void> GetViewsRpcHandler::operator()(GetViewsRPC &rpc, const GetViewsRPC::Request &request) const
{
    auto windows_result = co_await probe_handler->fetch_windows();
    if (not windows_result.has_value())
    {
        co_await rpc.finish_with_error(result2grpc_status(windows_result.error()));
        co_return;
    }

    GetViewsRPC::Response response;
    for (auto &&obj : windows_result.value())
    {
        auto &&proto_obj = response.add_object();
        proto_obj->set_type_id(obj.type_id);
        proto_obj->set_object_id(obj.type_id);
    }
    co_await rpc.finish(response, grpc::Status::OK);
}

agrpc::detail::RPCHandlerSender<GetViewsRPC, GetViewsRpcHandler> make_rpc_fetch_windows(
    agrpc::GrpcContext &grpc_context,
    quite::proto::ProbeService::AsyncService &service,
    ProbeHandlerHandle probe_handler)
{
    return agrpc::register_sender_rpc_handler<GetViewsRPC>(
        grpc_context, service, GetViewsRpcHandler{std::move(probe_handler)});
}

} // namespace quite::proto
```


