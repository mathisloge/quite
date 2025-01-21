#include "create_snapshot.hpp"
#include <QCoreApplication>
#include <QImage>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <fmt/format.h>
#include <quite/logger.hpp>
#include "../qtstdexec.h"
#include "../snapshot.hpp"
#include "grpc_error.hpp"
DEFINE_LOGGER(rpc_create_snapshot_logger)

namespace quite::probe
{
exec::task<void> CreateScreenshotRpcHandler::operator()(CreateScreenshotRPC &rpc,
                                                        const CreateScreenshotRPC::Request &request) const
{
    LOG_TRACE_L1(rpc_create_snapshot_logger(), "START RequestCreateScreenshot={}", request.object_id());
    CreateScreenshotRPC::Response response{};
    auto object =
        co_await stdexec::then(stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                               [&]() { return tracker.get_object_by_id(request.object_id()); });

    if (not object.has_value())
    {
        co_await rpc.finish(
            grpc::Status{grpc::StatusCode::NOT_FOUND, fmt::format("could not find {}", request.object_id())});
        co_return;
    }
    auto expected_image = co_await stdexec::starts_on(
        QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread()), take_snapshot(*object));
    if (expected_image.has_value())
    {
        constexpr std::int64_t k4Mb = 4000000;
        expected_image->convertTo(QImage::Format::Format_RGBA8888);
        response.mutable_metadata()->set_width(expected_image->width());
        response.mutable_metadata()->set_height(expected_image->height());

        std::int64_t remaining_bytes = expected_image->sizeInBytes();
        auto *data_begin = expected_image->bits();
        while (remaining_bytes > 0)
        {
            const auto to_be_send = std::min(remaining_bytes, k4Mb);
            auto *data_end = data_begin + to_be_send;
            std::copy(data_begin, data_end, std::back_inserter(*response.mutable_data()));

            const auto written = co_await rpc.write(response);
            if (not written)
            {
                co_await rpc.finish(grpc::Status::CANCELLED);
                co_return;
            }
            response.mutable_data()->clear();

            data_begin = std::next(data_begin, to_be_send);
            remaining_bytes -= to_be_send;
        }
        co_await rpc.finish(grpc::Status::OK);
        co_return;
    }
    co_await rpc.finish(error2grpc_status(expected_image.error()));
}

agrpc::detail::RPCHandlerSender<CreateScreenshotRPC, CreateScreenshotRpcHandler> create_snapshot(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service, ObjectTracker &tracker)
{
    return agrpc::register_sender_rpc_handler<CreateScreenshotRPC>(
        grpc_context, service, CreateScreenshotRpcHandler{tracker});
}
} // namespace quite::probe
