#include "create_snapshot.hpp"
#include <QCoreApplication>
#include <QImage>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include "../qtstdexec.h"
#include "../snapshot.hpp"

namespace quite::probe
{
exec::task<void> CreateScreenshotRpcHandler::operator()(CreateScreenshotRPC &rpc,
                                                        const CreateScreenshotRPC::Request &request)
{
    spdlog::trace("START RequestCreateScreenshot={}", request.object_id());
    CreateScreenshotRPC::Response response{};
    auto object =
        co_await stdexec::then(stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                               [&]() { return tracker.get_object_by_id(request.object_id()); });

    if (not object.has_value())
    {
        co_await rpc.finish(
            response, grpc::Status{grpc::StatusCode::NOT_FOUND, fmt::format("could not find {}", request.object_id())});
        co_return;
    }
    auto expected_image = co_await stdexec::on(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread()),
                                               take_snapshot(*object));
    if (expected_image.has_value())
    {
        expected_image->convertTo(QImage::Format::Format_RGBA8888);
        response.mutable_metadata()->set_width(expected_image->width());
        response.mutable_metadata()->set_height(expected_image->height());
        std::copy(expected_image->bits(),
                  expected_image->bits() + expected_image->sizeInBytes(),
                  std::back_inserter(*response.mutable_data()));
        co_await rpc.finish(response, grpc::Status::OK);
        co_return;
    }
    co_await rpc.finish(response,
                        grpc::Status{grpc::StatusCode::RESOURCE_EXHAUSTED,
                                     fmt::format("could not take image snapshot {}", request.object_id())});
}

agrpc::detail::RPCHandlerSender<CreateScreenshotRPC, CreateScreenshotRpcHandler> create_snapshot(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service, ObjectTracker &tracker)
{
    return agrpc::register_sender_rpc_handler<CreateScreenshotRPC>(
        grpc_context, service, CreateScreenshotRpcHandler{tracker});
}
} // namespace quite::probe
