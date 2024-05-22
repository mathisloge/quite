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

static auto get_object_properties(agrpc::GrpcContext &grpc_context,
                                quite::proto::ProbeService::AsyncService &service,
                                ObjectTracker &tracker)
{
    using RPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestGetObjectProperties>;
    return agrpc::register_sender_rpc_handler<RPC>(
        grpc_context, service, [&](RPC &rpc, const RPC::Request &request) -> exec::task<void> {
            spdlog::trace("START RequestGetObjectProperty={}", request.object_id());
            RPC::Response response{};
            co_await stdexec::then(
                stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())), [&]() {
                    for (auto &&property_name : request.property_names())
                    {
                        auto prop = tracker.get_property(request.object_id(), property_name);
                        if (prop.has_value())
                        {
                            response.mutable_property_values()->emplace(property_name, prop.value());
                        }
                    }
                });
            co_await rpc.finish(response, grpc::Status::OK);
        });
}
} // namespace quite::probe
