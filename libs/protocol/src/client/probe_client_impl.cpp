#include "probe_client_impl.hpp"
#include <boost/asio/steady_timer.hpp>
#include <agrpc/notify_on_state_change.hpp>
#include <exec/repeat_effect_until.hpp>
#include <exec/when_any.hpp>
#include <grpcpp/create_channel.h>
#include <quite/asio2exec.hpp>
#include <quite/logger.hpp>

DEFINE_LOGGER(probe_client)

namespace quite::proto
{
ProbeClientImpl::ProbeClientImpl(GrpcManager &grpc_manager, std::string connection_url)
    : grpc_context_{grpc_manager.context()}
    , grpc_channel_{::grpc::CreateChannel(std::move(connection_url), ::grpc::InsecureChannelCredentials())}
{}

AsyncResult<void> ProbeClientImpl::wait_for_connected(std::chrono::seconds timeout)
{
    auto state = grpc_channel_->GetState(true);
    if (state == grpc_connectivity_state::GRPC_CHANNEL_READY)
    {
        co_return {};
    }

    Result<void> return_result = make_error_result<void>(ErrorCode::unknown, "not initialized");
    boost::asio::steady_timer timer{entt::locator<asio2exec::asio_context>::value().get_executor(), timeout};
    co_await exec::when_any(
        agrpc::notify_on_state_change(*grpc_context_,
                                      *grpc_channel_,
                                      state,
                                      std::chrono::system_clock::now() + std::chrono::seconds(5),
                                      agrpc::use_sender) |
            stdexec::then([this, &return_result](bool state_changed) {
                if (not state_changed)
                {
                    return false;
                }
                const auto state = grpc_channel_->GetState(false);
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
            LOG_DEBUG(probe_client(), "timeout");
            return_result =
                make_error_result<void>(ErrorCode::deadline_exceeded, "Could not get connection state in time");
        }));
    co_return return_result;
}

IProbeService &ProbeClientImpl::probe_service()
{
    return probe_service_;
}

core::IMouseInjector &ProbeClientImpl::mouse_injector()
{
    return mouse_injector_;
}

meta::MetaRegistry &ProbeClientImpl::meta_registry()
{
    return meta_registry_;
}
} // namespace quite::proto
