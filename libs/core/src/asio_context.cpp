#include <entt/locator/locator.hpp>
#include <execpools/asio/asio_thread_pool.hpp>
#include <quite/asio_context.hpp>

namespace quite
{
execpools::asio_thread_pool &thread_pool()
{
    return entt::locator<execpools::asio_thread_pool>::value_or(2);
}

auto get_executor() -> decltype(thread_pool().get_executor())
{
    return thread_pool().get_executor();
}
} // namespace quite
