#include "quite/object_service.hpp"
#include <agrpc/asio_grpc.hpp>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <stdexec/execution.hpp>
#include "quite/detail/awaitable_server.hpp"
#include "quite/detail/rethrow.hpp"

namespace quite
{

using RpcSayHello = awaitable_server_t<&quite::proto::ObjectService::AsyncService::RequestSayHello>;
using RpcFindObject = awaitable_server_t<&quite::proto::ObjectService::AsyncService::RequestFindObject>;

using RpcFindObjectSender = agrpc::ServerRPC<&quite::proto::ObjectService::AsyncService::RequestFindObject>;

ObjectService::ObjectService(agrpc::GrpcContext &context, grpc::ServerBuilder &builder)
{
    builder.RegisterService(&service_);

    find_obj_ = agrpc::register_sender_rpc_handler<RpcFindObjectSender>(
        context, service_, [this](RpcFindObjectSender &rpc, const RpcFindObjectSender::Request &request) {
            return stdexec::then(stdexec::just(RpcFindObjectSender::Response{}), [this, &request](auto &&response) {
                onFindObject(request, response);
                return response;
            });
        });

    agrpc::register_awaitable_rpc_handler<RpcSayHello>(
        context,
        service_,
        [this](RpcSayHello &rpc, RpcSayHello::Request &request) -> asio::awaitable<void> {
            proto::HelloReply response;
            request.name();
            onSayHello(request, response);
            co_await rpc.finish(response, grpc::Status::OK);
        },
        RethrowFirstArg{});

    //agrpc::register_awaitable_rpc_handler<RpcFindObject>(
    //    context,
    //    service_,
    //    [this](RpcFindObject &rpc, RpcFindObject::Request &request) -> asio::awaitable<void> {
    //        proto::ObjectReply response;
//
    //        onFindObject(request, response);
    //        co_await rpc.finish(response, grpc::Status::OK);
    //    },
    //    RethrowFirstArg{});
}

ObjectService::~ObjectService() = default;

} // namespace quite
