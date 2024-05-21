#pragma once
#include <QCoreApplication>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include <spdlog/spdlog.h>
#include "../injector/mouse_injector.hpp"
#include "../qtstdexec.h"
namespace quite::probe
{

static auto mouse_click(agrpc::GrpcContext &grpc_context,
                        quite::proto::ProbeService::AsyncService &service,
                        MouseInjector &mouse_injector)
{
    using RPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestMouseAction>;
    return agrpc::register_sender_rpc_handler<RPC>(
        grpc_context, service, [&](RPC &rpc, const RPC::Request &request) -> exec::task<void> {
            spdlog::trace("START RequestMouseAction={}", request.object_id());
            RPC::Response response{};
            co_await stdexec::then(
                stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())), [&]() {
                    return mouse_injector.perform_action(request.object_id(),
                                                         request.mouse_action(),
                                                         request.mouse_button(),
                                                         request.modifier_key(),
                                                         request.relative_point());
                });

            if (true)
            {
                co_await rpc.finish(response, grpc::Status::OK);
            }
            else
            {
                co_await rpc.finish(
                    response,
                    grpc::Status{grpc::StatusCode::NOT_FOUND, fmt::format("could not find {}", request.object_id())});
            }
        });
}
} // namespace quite::probe
