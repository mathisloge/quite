// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <gtest/gtest.h>
#include <quite/test/remote_object.hpp>
#include "value_convert.hpp"

namespace quite::test
{
namespace
{
template <typename T>
T round_trip(T value)
{
    const Property::Value property_value = convert_any(entt::meta_any{value});
    const entt::meta_any any_value = convert_any(property_value);
    return std::get<T>(convert_any(any_value));
}
} // namespace

TEST(ValueConvert, RoundTripsBool)
{
    EXPECT_EQ(round_trip(true), true);
    EXPECT_EQ(round_trip(false), false);
}

TEST(ValueConvert, RoundTripsSignedInteger)
{
    EXPECT_EQ(round_trip<std::int64_t>(-42), -42);
}

TEST(ValueConvert, RoundTripsUnsignedInteger)
{
    EXPECT_EQ(round_trip<std::uint64_t>(42), 42u);
}

TEST(ValueConvert, RoundTripsDouble)
{
    EXPECT_DOUBLE_EQ(round_trip<double>(3.5), 3.5);
}

TEST(ValueConvert, RoundTripsString)
{
    EXPECT_EQ(round_trip<std::string>("hello"), "hello");
}

TEST(ValueConvert, UnknownTypeConvertsToFalse)
{
    const entt::meta_any unknown{std::vector<int>{1, 2, 3}};
    const Property::Value converted = convert_any(unknown);
    ASSERT_TRUE(std::holds_alternative<bool>(converted));
    EXPECT_FALSE(std::get<bool>(converted));
}
} // namespace quite::test
