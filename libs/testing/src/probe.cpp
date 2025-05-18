#include "quite/test/probe.hpp"
#include <boost/asio/steady_timer.hpp>
#include <asioexec/use_sender.hpp>
#include <exec/repeat_effect_until.hpp>
#include <exec/task.hpp>
#include <exec/when_any.hpp>
#include <quite/asio_context.hpp>
#include <quite/client/quite.hpp>
#include <quite/client/remote_object.hpp>
#include <quite/value/object_query.hpp>
#include "quite/client/probe.hpp"
#include "throw_unexpected.hpp"

namespace quite::test
{
Probe::~Probe() = default;

Probe::Probe(Probe &&) noexcept = default;

Probe &Probe::operator=(Probe &&) noexcept = default;

Probe::Probe(client::ProbeHandle handle)
    : handle_{std::move(handle)}
{}

void Probe::wait_for_connected(std::chrono::seconds timeout)
{
    const auto [is_connected] = stdexec::sync_wait(handle_->wait_for_started(timeout)).value();
    throw_unexpected(is_connected);
}

RemoteObject Probe::find_object(std::shared_ptr<ObjectQuery> query)
{
    auto [obj] = stdexec::sync_wait(handle_->find_object(*query)).value();
    throw_unexpected(obj);
    return RemoteObject{std::move(*obj)};
}

RemoteObject Probe::try_find_object(std::shared_ptr<ObjectQuery> query, std::chrono::milliseconds timeout)
{
    Result<client::RemoteObjectPtr> found_object;
    stdexec::sender auto find_obj_snd =
        stdexec::when_all(stdexec::just(handle_), stdexec::just(std::move(query))) |
        stdexec::continues_on(client::asio_context().get_scheduler()) |
        stdexec::let_value([](auto handle, auto query) { return handle->find_object(*query); }) |
        stdexec::then([&found_object](auto &&result) {
            found_object = std::forward<decltype(result)>(result);
            return found_object.has_value();
        }) |
        exec::repeat_effect_until();

    boost::asio::steady_timer timer{get_executor(), timeout};
    stdexec::sender auto timeout_snd =
        timer.async_wait(asioexec::use_sender) | stdexec::then([&found_object](auto &&...) {
            found_object = quite::make_error_result(ErrorCode::deadline_exceeded, "Could not find object in time.");
        });
    stdexec::sender auto wait_snd = exec::when_any(std::move(find_obj_snd), std::move(timeout_snd));
    stdexec::sync_wait(std::move(wait_snd));
    throw_unexpected(found_object);
    return RemoteObject{std::move(*found_object)};
}

void Probe::exit()
{
    stdexec::sync_wait(handle_->exit());
}
} // namespace quite::test
