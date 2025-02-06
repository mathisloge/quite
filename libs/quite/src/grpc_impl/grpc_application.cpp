#include "grpc_application.hpp"
#include <boost/asio/steady_timer.hpp>
#include <agrpc/asio_grpc.hpp>
#include <exec/repeat_effect_until.hpp>
#include <exec/when_any.hpp>
#include <grpcpp/channel.h>
#include <quite/logger.hpp>
#include "grpc_remote_object.hpp"
#include "probe_client.hpp"
#include "rpc/make_exit_request.hpp"
#include "rpc/make_find_object_request.hpp"
#include "rpc/make_get_views_request.hpp"

DEFINE_LOGGER(grpc_app_logger)

namespace quite::grpc_impl
{
GrpcApplication::GrpcApplication(Context &context)
    : probe_handle_{std::make_shared<grpc_impl::ProbeClient>(context.grpcContext())}
    , meta_type_registry_{probe_handle_}
{}

AsyncResult<void> GrpcApplication::wait_for_started()
{
    auto state = probe_handle_->channel().GetState(true);
    if (state == grpc_connectivity_state::GRPC_CHANNEL_READY)
    {
        co_return {};
    }

    Result<void> return_result = make_error_result<void>(ErrorCode::unknown, "not initialized");
    boost::asio::steady_timer timer{Context::Instance().asioContext().get_executor(), std::chrono::seconds(10)};
    co_await exec::when_any(
        agrpc::notify_on_state_change(probe_handle_->context(),
                                      probe_handle_->channel(),
                                      state,
                                      std::chrono::system_clock::now() + std::chrono::seconds(5),
                                      agrpc::use_sender) |
            stdexec::then([this, &return_result](bool state_changed) {
                if (not state_changed)
                {
                    return false;
                }
                const auto state = probe_handle_->channel().GetState(false);
                if (state == grpc_connectivity_state::GRPC_CHANNEL_READY)
                {
                    return_result = Result<void>{};
                    return true;
                }
                if (state == grpc_connectivity_state::GRPC_CHANNEL_SHUTDOWN)
                {
                    return_result = make_error_result<void>(ErrorCode::cancelled,
                                                            "Channel had an unrecoverable error or was shutdown.");
                    return true;
                }
                return false;
            }) |
            exec::repeat_effect_until(),
        timer.async_wait(asio2exec::use_sender) | stdexec::then([&return_result](std::error_code) {
            return_result =
                make_error_result<void>(ErrorCode::deadline_exceeded, "Could not get connection state in time");
        }));
    co_return return_result;
}

AsyncResult<std::shared_ptr<RemoteObject>> GrpcApplication::find_object(const ObjectQuery &query)
{
    LOG_DEBUG(grpc_app_logger(), "Starting request with object_name={}", fmt::format("{}", query));
    const auto response =
        co_await grpc_impl::make_find_object_request(probe_handle_->context(), probe_handle_->stub(), query);
    co_return response.and_then([&](const proto::ObjectReply &reply) -> Result<std::shared_ptr<RemoteObject>> {
        return std::make_shared<GrpcRemoteObject>(reply.object_id(), reply.type_id(), probe_handle_);
    });
}

AsyncResult<std::vector<std::shared_ptr<RemoteObject>>> GrpcApplication::get_views()
{
    LOG_TRACE_L1(grpc_app_logger(), "Requesting top level views from {}", "[TODO:APPNAME]");
    const auto response = co_await grpc_impl::make_get_views_request(probe_handle_->context(), probe_handle_->stub());
    co_return response.and_then(
        [&](const proto::GetViewsResponse &reply) -> Result<std::vector<std::shared_ptr<RemoteObject>>> {
            std::vector<std::shared_ptr<RemoteObject>> views;
            views.reserve(reply.object_size());
            for (auto &&obj : reply.object())
            {
                views.emplace_back(
                    std::make_shared<grpc_impl::GrpcRemoteObject>(obj.object_id(), obj.type_id(), probe_handle_));
            }
            return views;
        });
}

AsyncResult<void> GrpcApplication::exit()
{
    LOG_TRACE_L1(grpc_app_logger(), "Request exiting application {}", "[TODO:APPNAME]");
    const auto response = co_await grpc_impl::make_exit_request(probe_handle_->context(), probe_handle_->stub());
    co_return response.and_then([&](const proto::ExitReponse & /*reply*/) -> Result<void> { return {}; });
}

meta::MetaRegistry &GrpcApplication::meta_registry()
{
    return meta_type_registry_;
}

} // namespace quite::grpc_impl
