#include "context.hpp"
#include <quite/asio_context.hpp>
#include <quite/value/value_registry.hpp>

namespace quite
{

Context::Context()
{
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
    return thread_pool();
}

Context &Context::Instance()
{
    static Context context;
    return context;
}
} // namespace quite
