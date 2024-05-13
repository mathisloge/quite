#pragma once
#include <QCoreApplication>
#include <QImage>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <exec/async_scope.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include <spdlog/spdlog.h>
#include "../object_tracker.hpp"
#include "../qtstdexec.h"
#include "../screenshot.hpp"
namespace quite::probe
{

static auto create_screenshot(agrpc::GrpcContext &grpc_context,
                              quite::proto::ProbeService::AsyncService &service,
                              ObjectTracker &tracker)
{
    using RPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestCreateScreenshot>;
    return agrpc::register_sender_rpc_handler<RPC>(
        grpc_context, service, [&](RPC &rpc, const RPC::Request &request) -> exec::task<void> {
            spdlog::trace("START RequestMouseClick={}", request.id());
            RPC::Response response{};
            auto object = co_await stdexec::then(
                stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                [&]() { return tracker.get_object_by_id(reinterpret_cast<QObject *>(request.id())); });

            if (!object.has_value())
            {
                co_await rpc.finish(
                    response,
                    grpc::Status{grpc::StatusCode::NOT_FOUND, fmt::format("could not find {}", request.id())});
            }
            auto expected_image = co_await stdexec::on(
                QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread()), take_snapshot(*object));
            if (expected_image.has_value())
            {
                expected_image->convertTo(QImage::Format::Format_RGBA8888);
                response.mutable_metadata()->set_width(expected_image->width());
                response.mutable_metadata()->set_height(expected_image->height());
                std::copy(expected_image->bits(),
                          expected_image->bits() + expected_image->sizeInBytes(),
                          std::back_inserter(*response.mutable_data()));
                expected_image.value().save("/home/mathis/dev/ng-quite/test.png");
                co_await rpc.finish(response, grpc::Status::OK);
            }
            co_await rpc.finish(response,
                                grpc::Status{grpc::StatusCode::RESOURCE_EXHAUSTED,
                                             fmt::format("could not take image snapshot {}", request.id())});
        });
}
} // namespace quite::probe
