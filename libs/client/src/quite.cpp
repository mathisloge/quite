// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "quite/client/quite.hpp"
#include "context.hpp"

namespace quite::client
{
exec::asio::asio_thread_pool &asio_context()
{
    return Context::Instance().asio_context();
}
} // namespace quite::client
