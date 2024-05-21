#pragma once
#include <QCoreApplication>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <exec/task.hpp>
#include <fmt/compile.h>
#include <quite/proto/probe.grpc.pb.h>
#include <spdlog/spdlog.h>
#include "../object_tracker.hpp"
#include "../qtstdexec.h"
namespace quite::probe
{

static auto find_object_rpc(agrpc::GrpcContext &grpc_context,
                            quite::proto::ProbeService::AsyncService &service,
                            ObjectTracker &tracker)
{
    using RpcFindObjectSender = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestFindObject>;
    return agrpc::register_sender_rpc_handler<RpcFindObjectSender>(
        grpc_context,
        service,
        [&](RpcFindObjectSender &rpc, const RpcFindObjectSender::Request &request) -> exec::task<void> {
            spdlog::debug("START RpcFindObject");

            RpcFindObjectSender::Response response{};
            auto obj_info = co_await stdexec::then(
                stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                [&]() -> std::expected<ObjectInfo, ObjectErrC> {
                    auto it = request.query().properties().find("objectName");
                    if (it != request.query().properties().end())
                    {
                        return tracker.findObject(it->second);
                    }
                    return std::unexpected(ObjectErrC::not_found);
                });

            if (obj_info.has_value())
            {
                response.set_object_id(obj_info->object_id);
                co_await rpc.finish(response, grpc::Status::OK);
            }
            else
            {
                co_await rpc.finish(response, grpc::Status{grpc::StatusCode::NOT_FOUND, fmt::format("could not find")});
            }
        });
}
} // namespace quite::probe
