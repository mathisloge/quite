// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

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
    get_executor().context().stop();
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
