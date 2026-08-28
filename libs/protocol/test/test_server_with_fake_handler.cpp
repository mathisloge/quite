// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <fmt/format.h>
#include <gtest/gtest.h>
#include <quite/proto/client/client.hpp>
#include <quite/proto/client/probe_client.hpp>
#include <quite/proto/client/value_converter.hpp>
#include <quite/proto/probe/server.hpp>
#include <quite/value/value_registry.hpp>
#include <unistd.h>
#include "fake_probe_handler.hpp"

using namespace quite;
using namespace quite::proto;
using namespace quite::proto::test;

namespace
{
std::string unique_socket_url()
{
    return fmt::format("unix:///tmp/quite_test_fake_handler_{}.sock", getpid());
}

class NullValueConverter final : public IValueConverter
{
  public:
    entt::meta_any from(ObjectReference /*ref*/) const override
    {
        return {};
    }
};
} // namespace

TEST(ServerWithFakeHandler, FindObjectRoundTripsThroughRealTransport)
{
    const auto url = unique_socket_url();

    Server server{url,
                  ServiceHandle<IProbeHandler>{std::make_shared<FakeProbeHandler>()},
                  {},
                  {},
                  ServiceHandle<ValueRegistry>{std::make_shared<ValueRegistry>()}};

    entt::locator<ValueRegistry>::emplace();
    Client client{entt::locator<ValueRegistry>::handle()};
    auto probe_client = client.create_probe_client(std::make_shared<NullValueConverter>(), url);

    auto [connected] = stdexec::sync_wait(probe_client->wait_for_connected(std::chrono::seconds(5))).value();
    ASSERT_TRUE(connected.has_value());

    auto [result] = stdexec::sync_wait(probe_client->probe_service().find_object(ObjectQuery{})).value();

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->object_id, 99u);
    EXPECT_EQ(result->type_id, 3u);
}
