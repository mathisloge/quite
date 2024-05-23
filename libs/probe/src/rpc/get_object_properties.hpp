#pragma once
#include <QCoreApplication>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include <spdlog/spdlog.h>
#include "../object_tracker.hpp"
#include "../property_collector.hpp"
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
                    if (request.property_names_size() == 0)
                    {
                        auto obj = tracker.get_object_by_id(request.object_id());
                        auto properties = collect_properties(ObjectMeta::from_qobject(*obj));
                        response.mutable_property_values()->insert(properties.begin(), properties.end());
                    }
                    else
                    {
                        for (auto &&property_name : request.property_names())
                        {
                            auto prop = tracker.get_property(request.object_id(), property_name);
                            if (prop.has_value())
                            {
                                response.mutable_property_values()->emplace(property_name, prop.value());
                            }
                        }
                    }
                });
            co_await rpc.finish(response, grpc::Status::OK);
        });
}
} // namespace quite::probe
