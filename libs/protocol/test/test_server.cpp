// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <thread>
#include <fmt/format.h>
#include <gtest/gtest.h>
#include <quite/proto/probe/server.hpp>
#include <unistd.h>

namespace
{
std::string unique_socket_url()
{
    return fmt::format("unix:///tmp/quite_test_server_{}.sock", getpid());
}
} // namespace

TEST(ProtocolServer, ShutdownInstant)
{
    const auto url = unique_socket_url();
    for (int i = 0; i < 1000; ++i)
    {
        quite::proto::Server server{url, {}, {}, {}, {}};
    }
}

TEST(ProtocolServer, ShutdownDelayed)
{
    quite::proto::Server server{unique_socket_url(), {}, {}, {}, {}};
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
