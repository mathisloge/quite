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

static auto get_object_property(agrpc::GrpcContext &grpc_context,
                     quite::proto::ObjectService::AsyncService &service,
                     ObjectTracker &tracker)
{
    using RPC = agrpc::ServerRPC<&quite::proto::ObjectService::AsyncService::RequestGetObjectProperty>;
    return agrpc::register_sender_rpc_handler<RPC>(
        grpc_context,
        service,
        [&](RPC &rpc, const RPC::Request &request) -> exec::task<void> {
            spdlog::trace("START RequestGetObjectProperty={}", request.id());
            RPC::Response response{};
            auto property_value = co_await stdexec::then(
                stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                [&]() { return tracker.get_property(reinterpret_cast<QObject*>(request.id()), request.property_name()); });

            if (property_value.has_value())
            {
                *response.mutable_value() = std::move(*property_value);
                co_await rpc.finish(response, grpc::Status::OK);
            }
            else
            {
                co_await rpc.finish(
                    response,
                    grpc::Status{grpc::StatusCode::NOT_FOUND, fmt::format("could not find {}", request.id())});
            }
        });
}
} // namespace quite::probe
