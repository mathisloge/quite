// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <entt/meta/container.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/resolve.hpp>
#include <gtest/gtest.h>
#include <quite/value/value_registry.hpp>
#include "value.hpp"

using namespace entt::literals;

namespace quite::proto
{
namespace
{
class NullValueConverter final : public IValueConverter
{
  public:
    entt::meta_any from(ObjectReference /*ref*/) const override
    {
        return {};
    }
};
} // namespace

TEST(ValueConversion, ArrayValueRoundTrips)
{
    // entt only treats a type as a sequence container once entt::meta_factory registers it
    entt::meta_factory<std::vector<std::int64_t>>().type("ValueConversionTestIntVector"_hs);
    entt::meta_factory<std::vector<entt::meta_any>>().type("ValueConversionTestAnyVector"_hs);

    ValueRegistry registry;
    NullValueConverter converter;

    const entt::meta_any input{std::vector<std::int64_t>{10, 20, 30}};
    const Value encoded = create_value(registry, input);
    ASSERT_TRUE(encoded.has_array_val());
    ASSERT_EQ(encoded.array_val().value_size(), 3);

    const entt::meta_any decoded = convert_value(registry, converter, encoded);
    ASSERT_TRUE(decoded.type().is_sequence_container());
    auto seq = decoded.as_sequence_container();
    ASSERT_EQ(seq.size(), 3u);
    // elements are double-wrapped meta_any; unwrap once before the inner scalar
    auto it = seq.begin();
    EXPECT_EQ((*it).cast<entt::meta_any>().cast<std::int64_t>(), 10);
    ++it;
    EXPECT_EQ((*it).cast<entt::meta_any>().cast<std::int64_t>(), 20);
    ++it;
    EXPECT_EQ((*it).cast<entt::meta_any>().cast<std::int64_t>(), 30);
}

namespace
{
// std::string minus substr(): entt's sequence-container concept excludes types with substr(),
// which is why std::string never qualifies but QString (uses .mid()) does once registered.
class StringLikeContainer : private std::string
{
  public:
    using std::string::begin;
    using std::string::cbegin;
    using std::string::cend;
    using std::string::const_reference;
    using std::string::end;
    using std::string::iterator;
    using std::string::size;
    using std::string::string;
    using std::string::value_type;

    const std::string &as_std_string() const
    {
        return *this;
    }
};
} // namespace

// string-convertible types that are also sequence containers must still encode as strings
TEST(ValueConversion, StringLikeContainerValueEncodesAsStringNotArray)
{
    entt::meta_factory<StringLikeContainer>()
        .type("ValueConversionTestStringLikeContainer"_hs)
        .conv<[](auto &&value) { return value.as_std_string(); }>();

    ValueRegistry registry;
    NullValueConverter converter;

    const entt::meta_any input{StringLikeContainer{"hello"}};
    ASSERT_TRUE(input.type().is_sequence_container());
    ASSERT_TRUE(input.type().can_convert(entt::resolve<std::string>()));

    const Value encoded = create_value(registry, input);
    ASSERT_TRUE(encoded.has_string_val());
    EXPECT_EQ(encoded.string_val(), "hello");

    const entt::meta_any decoded = convert_value(registry, converter, encoded);
    ASSERT_TRUE(decoded.allow_cast<std::string>());
    EXPECT_EQ(decoded.cast<std::string>(), "hello");
}
} // namespace quite::proto
