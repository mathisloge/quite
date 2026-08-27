// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <entt/locator/locator.hpp>
#include <exec/asio/asio_thread_pool.hpp>
#include <quite/asio_context.hpp>

namespace quite
{
exec::asio::asio_thread_pool &thread_pool()
{
    return entt::locator<exec::asio::asio_thread_pool>::value_or(2);
}

auto get_executor() -> decltype(thread_pool().get_executor())
{
    return thread_pool().get_executor();
}
} // namespace quite
