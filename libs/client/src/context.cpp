#include "context.hpp"
#include <execpools/asio/asio_thread_pool.hpp>
#include <quite/asio_context.hpp>
#include <quite/value/value_registry.hpp>

namespace quite
{

Context::Context()
{
    create_asio_context();
    entt::locator<ValueRegistry>::emplace();
    client_ = std::make_unique<proto::Client>(entt::locator<ValueRegistry>::handle());
}

Context::~Context()
{
    asio_impl::query(thread_pool().executor(), asio_impl::execution::context_t{}).stop();
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
