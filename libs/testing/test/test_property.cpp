// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <gtest/gtest.h>
#include <quite/test/property.hpp>
#include <quite/test/remote_object.hpp>
#include "fakes/fake_property.hpp"

namespace quite::test
{

TEST(Property, WaitForValueReturnsTargetOnceReached)
{
    auto fake = std::make_shared<fakes::FakeProperty>(
        std::deque<entt::meta_any>{entt::meta_any{std::int64_t{1}}, entt::meta_any{std::int64_t{2}}});
    Property property{fake};

    const auto result = property.wait_for_value(Property::Value{std::int64_t{2}}, std::chrono::seconds(2));

    ASSERT_TRUE(std::holds_alternative<std::int64_t>(result));
    EXPECT_EQ(std::get<std::int64_t>(result), 2);
}

TEST(Property, WaitForValueReturnsLastValueOnTimeout)
{
    auto fake = std::make_shared<fakes::FakeProperty>(std::deque<entt::meta_any>{entt::meta_any{std::int64_t{1}}});
    Property property{fake};

    const auto result = property.wait_for_value(Property::Value{std::int64_t{999}}, std::chrono::milliseconds(150));

    ASSERT_TRUE(std::holds_alternative<std::int64_t>(result));
    EXPECT_EQ(std::get<std::int64_t>(result), 1);
}
} // namespace quite::test
