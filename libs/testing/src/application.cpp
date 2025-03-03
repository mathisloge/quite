#include "quite/test/application.hpp"
#include <boost/asio/steady_timer.hpp>
#include <exec/repeat_effect_until.hpp>
#include <exec/task.hpp>
#include <exec/when_any.hpp>
#include <quite/application.hpp>
#include <quite/quite.hpp>
#include <quite/value/object_query.hpp>
#include "throw_unexpected.hpp"

namespace quite::test
{
Application::~Application() = default;

Application::Application(Application &&) noexcept = default;

Application &Application::operator=(Application &&) noexcept = default;

Application::Application(std::shared_ptr<quite::Application> app)
    : app_{std::move(app)}
{}

void Application::wait_for_connected(std::chrono::seconds timeout)
{
    const auto [is_connected] = stdexec::sync_wait(app_->wait_for_started(timeout)).value();
    throw_unexpected(is_connected);
}

RemoteObject Application::find_object(std::shared_ptr<ObjectQuery> query)
{
    auto obj = std::get<Result<RemoteObjectPtr>>(
        stdexec::sync_wait([app = app_, query = std::move(query)]() -> AsyncResult<RemoteObjectPtr> {
            auto obj = co_await app->find_object(*query);
            co_return obj;
        }())
            .value());
    throw_unexpected(obj);
    return RemoteObject{std::move(*obj)};
}

RemoteObject Application::try_find_object(std::shared_ptr<ObjectQuery> query, std::chrono::milliseconds timeout)
{
    Result<RemoteObjectPtr> found_object;
    stdexec::sender auto find_obj_snd = stdexec::schedule(asio_context().get_scheduler()) |
                                        stdexec::let_value([this, query]() { return app_->find_object(*query); }) |
                                        stdexec::then([&found_object](auto &&result) {
                                            found_object = std::forward<decltype(result)>(result);
                                            return found_object.has_value();
                                        }) |
                                        exec::repeat_effect_until();

    boost::asio::steady_timer timer{asio_context().get_executor(), timeout};
    stdexec::sender auto timeout_snd =
        timer.async_wait(asio2exec::use_sender) | stdexec::then([&found_object](auto &&ec) {
            found_object = quite::make_error_result<RemoteObjectPtr>(ErrorCode::deadline_exceeded,
                                                                     "Could not find object in time.");
        });
    stdexec::sender auto wait_snd = exec::when_any(std::move(find_obj_snd), std::move(timeout_snd));
    stdexec::sync_wait(std::move(wait_snd));
    throw_unexpected(found_object);
    return RemoteObject{std::move(*found_object)};
}

void Application::exit()
{
    stdexec::sync_wait([app = app_]() -> exec::task<void> { co_await app->exit(); }());
}
} // namespace quite::test
