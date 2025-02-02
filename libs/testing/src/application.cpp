#include "quite/test/application.hpp"
#include <quite/application.hpp>
#include <quite/object_query.hpp>
#include "quite/test/exceptions.hpp"

namespace quite::test
{
Application::~Application() = default;

Application::Application(Application &&) noexcept = default;

Application &Application::operator=(Application &&) noexcept = default;

Application::Application(std::shared_ptr<quite::Application> app)
    : app_{std::move(app)}
{}

RemoteObject Application::find_object(std::shared_ptr<ObjectQuery> query)
{
    auto obj = std::get<Result<RemoteObjectPtr>>(
        stdexec::sync_wait([app = app_, query = std::move(query)]() -> AsyncResult<RemoteObjectPtr> {
            auto obj = co_await app->find_object(*query);
            co_return obj;
        }())
            .value());

    if (not obj.has_value())
    {
        throw RemoteException{std::move(obj.error())};
    }
    return RemoteObject{std::move(*obj)};
}

void Application::exit()
{
    stdexec::sync_wait([this]() -> exec::task<void> { co_await app_->exit(); }());
}
} // namespace quite::test
