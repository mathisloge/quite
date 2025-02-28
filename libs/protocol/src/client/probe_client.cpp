#include "quite/proto/client/probe_client.hpp"
#include <boost/asio/steady_timer.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/notify_on_state_change.hpp>
#include <entt/locator/locator.hpp>
#include <exec/repeat_effect_until.hpp>
#include <exec/when_any.hpp>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <quite/asio2exec.hpp>
#include "grpc_manager.hpp"
#include "probe_service_impl.hpp"
#include "quite/proto/meta_service.grpc.pb.h"
#include "quite/proto/probe.grpc.pb.h"

namespace quite::proto
{
struct ProbeClient::Impl
{
    Impl(std::string connection_url)
        : grpc_channel_{::grpc::CreateChannel(std::move(connection_url), ::grpc::InsecureChannelCredentials())}
    {}

    std::shared_ptr<agrpc::GrpcContext> grpc_context_{entt::locator<GrpcManager>::value_or().context()};
    std::shared_ptr<grpc::Channel> grpc_channel_;
    proto::ProbeService::Stub probe_service_stub_{grpc_channel_};
    proto::MetaService::Stub meta_service_stub_{grpc_channel_};
    ProbeServiceImpl probe_service_{grpc_context_, probe_service_stub_};
};

ProbeClient::ProbeClient(std::string connection_url)
    : impl_{std::make_unique<ProbeClient::Impl>(std::move(connection_url))}
{}

ProbeClient::~ProbeClient() = default;

AsyncResult<void> ProbeClient::wait_for_connected(std::chrono::seconds timeout)
{
    auto state = impl_->grpc_channel_->GetState(true);
    if (state == grpc_connectivity_state::GRPC_CHANNEL_READY)
    {
        co_return {};
    }

    Result<void> return_result = make_error_result<void>(ErrorCode::unknown, "not initialized");
    boost::asio::steady_timer timer{entt::locator<boost::asio::io_context>::value(), timeout};
    co_await exec::when_any(
        agrpc::notify_on_state_change(*impl_->grpc_context_,
                                      *impl_->grpc_channel_,
                                      state,
                                      std::chrono::system_clock::now() + std::chrono::seconds(5),
                                      agrpc::use_sender) |
            stdexec::then([this, &return_result](bool state_changed) {
                if (not state_changed)
                {
                    return false;
                }
                const auto state = impl_->grpc_channel_->GetState(false);
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

IProbeService &ProbeClient::probe_service()
{
    return impl_->probe_service_;
}

core::IMouseInjector &ProbeClient::mouse_injector()
{}

meta::MetaRegistry &ProbeClient::meta_registry()
{}

} // namespace quite::proto
