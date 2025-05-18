#include "context.hpp"
#include <execpools/asio/asio_thread_pool.hpp>
#include <quite/value/value_registry.hpp>

namespace quite
{

Context::Context()
{
    auto &asio_context = entt::locator<execpools::asio_thread_pool>::emplace(2);
    entt::locator<ValueRegistry>::emplace();
    client_ = std::make_unique<proto::Client>(entt::locator<ValueRegistry>::handle(),
                                              entt::locator<asio2exec::asio_context>::handle());
}

Context::~Context()
{
    entt::locator<asio2exec::asio_context>::value().stop();
}

proto::Client &Context::backend_client()
{
    return *client_;
}

execpools::asio_thread_pool &Context::asio_context()
{
    return entt::locator<execpools::asio_thread_pool>::value();
}

Context &Context::Instance()
{
    static Context context;
    return context;
}
} // namespace quite
