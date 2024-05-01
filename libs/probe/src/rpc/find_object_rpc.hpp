#pragma once
#include <QCoreApplication>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <exec/task.hpp>
#include <object/object.grpc.pb.h>
#include <spdlog/spdlog.h>
#include "../object_tracker.hpp"
#include "../qtstdexec.h"
namespace quite::probe
{

auto find_object_rpc(agrpc::GrpcContext &grpc_context,
                     quite::proto::ObjectService::AsyncService &service,
                     ObjectTracker &tracker)
{
    using RpcFindObjectSender = agrpc::ServerRPC<&quite::proto::ObjectService::AsyncService::RequestFindObject>;
    return agrpc::register_sender_rpc_handler<RpcFindObjectSender>(
        grpc_context,
        service,
        [&](RpcFindObjectSender &rpc, const RpcFindObjectSender::Request &request) -> exec::task<void> {
            spdlog::trace("START RpcFindObject={}", request.object_name());
            RpcFindObjectSender::Response response{};
            auto obj_info = co_await stdexec::then(
                stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                [&]() { return tracker.findObject(request.object_name()); });

            if (obj_info.has_value())
            {
                response.set_id(obj_info->object_id);
                *response.mutable_type_name() = obj_info->class_type;
                co_await rpc.finish(response, grpc::Status::OK);
            }
            else
            {
                co_await rpc.finish(
                    response,
                    grpc::Status{grpc::StatusCode::NOT_FOUND, fmt::format("could not find {}", request.object_name())});
            }
        });
}
} // namespace quite::probe
