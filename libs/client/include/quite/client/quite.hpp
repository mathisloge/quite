// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <boost/asio/any_io_executor.hpp>
#include <exec/asio/asio_thread_pool.hpp>
#include "quite/quite_client_export.hpp"

namespace quite::client
{
QUITE_CLIENT_EXPORT exec::asio::asio_thread_pool &asio_context();
} // namespace quite::client
