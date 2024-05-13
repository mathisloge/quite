#pragma once
#include <QCoreApplication>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include <spdlog/spdlog.h>
#include "../object_tracker.hpp"
#include "../qtstdexec.h"
namespace quite::probe
{

static auto mouse_click(agrpc::GrpcContext &grpc_context,
                 quite::proto::ProbeService::AsyncService &service,
                 ObjectTracker &tracker)
{
    using RPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestMouseClick>;
    return agrpc::register_sender_rpc_handler<RPC>(
        grpc_context, service, [&](RPC &rpc, const RPC::Request &request) -> exec::task<void> {
            spdlog::trace("START RequestMouseClick={}", request.target_id());
            RPC::Response response{};
            co_await stdexec::then(
                stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                [&]() { return tracker.mouse_click(reinterpret_cast<QObject *>(request.target_id())); });

            if (true)
            {
                co_await rpc.finish(response, grpc::Status::OK);
            }
            else
            {
                co_await rpc.finish(
                    response,
                    grpc::Status{grpc::StatusCode::NOT_FOUND, fmt::format("could not find {}", request.target_id())});
            }
        });
}
} // namespace quite::probe
