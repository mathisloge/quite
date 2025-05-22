#include <entt/locator/locator.hpp>
#include <execpools/asio/asio_thread_pool.hpp>
#include <quite/asio_context.hpp>

namespace quite
{
void create_asio_context()
{
    entt::locator<execpools::asio_thread_pool>::emplace(2);
}

execpools::asio_thread_pool &thread_pool()
{
    return entt::locator<execpools::asio_thread_pool>::value_or(2);
}

auto get_executor() -> decltype(thread_pool().executor())
{
    return entt::locator<execpools::asio_thread_pool>::value_or(2).executor();
}
} // namespace quite
