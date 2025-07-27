

# File probe\_client\_impl.cpp

[**File List**](files.md) **>** [**client**](dir_5522d6aca5c3fb454e911c5582f2e576.md) **>** [**probe\_client\_impl.cpp**](probe__client__impl_8cpp.md)

[Go to the documentation of this file](probe__client__impl_8cpp.md)


```C++
#include "probe_client_impl.hpp"
#include <boost/asio/steady_timer.hpp>
#include <agrpc/notify_on_state_change.hpp>
#include <asioexec/use_sender.hpp>
#include <exec/repeat_effect_until.hpp>
#include <exec/when_any.hpp>
#include <grpcpp/create_channel.h>
#include <quite/asio_context.hpp>
#include <quite/logger.hpp>

DEFINE_LOGGER(probe_client)

namespace quite::proto
{
ProbeClientImpl::ProbeClientImpl(GrpcManager &grpc_manager,
                                 std::string connection_url,
                                 std::shared_ptr<IValueConverter> value_converter)
    : grpc_context_{grpc_manager.context()}
    , grpc_channel_{::grpc::CreateChannel(std::move(connection_url), ::grpc::InsecureChannelCredentials())}
    , value_converter_{std::move(value_converter)}
{}

AsyncResult<void> ProbeClientImpl::wait_for_connected(std::chrono::seconds timeout)
{
    auto state = grpc_channel_->GetState(true);
    if (state == grpc_connectivity_state::GRPC_CHANNEL_READY)
    {
        co_return {};
    }

    const auto deadline = std::chrono::system_clock::now() + timeout;
    bool is_connected{false};
    while (not is_connected)
    {
        const auto state_change_result = co_await stdexec::starts_on(
            exec::inline_scheduler{},
            agrpc::notify_on_state_change(*grpc_context_, *grpc_channel_, state, deadline, agrpc::use_sender) |
                stdexec::then([this, &state](bool state_changed) -> Result<bool> {
                    if (not state_changed)
                    {
                        return make_error_result(ErrorCode::deadline_exceeded,
                                                 "Could not get connection state in time.");
                    }
                    state = grpc_channel_->GetState(true);
                    LOG_DEBUG(probe_client(), "state: {}", static_cast<int>(state));
                    if (state == grpc_connectivity_state::GRPC_CHANNEL_READY)
                    {
                        return true;
                    }
                    if (state == grpc_connectivity_state::GRPC_CHANNEL_SHUTDOWN)
                    {
                        return make_error_result(ErrorCode::cancelled,
                                                 "Channel had an unrecoverable error or was shutdown.");
                    }
                    return false;
                }));
        if (state_change_result.has_value())
        {
            is_connected = state_change_result.value();
        }
        else
        {
            co_return std::unexpected{state_change_result.error()};
        }
    }
    co_return {};
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
```


