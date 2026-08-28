// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <entt/meta/container.hpp>
#include <entt/meta/factory.hpp>
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

// Regression test: create_value used to check type.is_class() before type.is_sequence_container(),
// and STL-style containers are also is_class(), so every array value silently became an empty
// class value instead of an array. Exercises create_value/convert_value directly (no Server/Client)
// so the encode+decode round trip can be verified in isolation.
TEST(ValueConversion, ArrayValueRoundTrips)
{
    // entt only recognizes a type as a sequence container once it has an entt::meta_factory
    // registration in the (process-wide default) meta context; mirrors how real callers (e.g.
    // probeqt's register_converters) must register their container types up front. Both the
    // input type and the type convert_value's array_val decode path produces
    // (std::vector<entt::meta_any>) need it.
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
    // Each element of the decoded std::vector<entt::meta_any> is itself wrapped in an
    // entt::meta_any by the generic sequence-container iteration, so it needs an extra
    // cast<entt::meta_any>() unwrap before the inner scalar is reachable.
    auto it = seq.begin();
    EXPECT_EQ((*it).cast<entt::meta_any>().cast<std::int64_t>(), 10);
    ++it;
    EXPECT_EQ((*it).cast<entt::meta_any>().cast<std::int64_t>(), 20);
    ++it;
    EXPECT_EQ((*it).cast<entt::meta_any>().cast<std::int64_t>(), 30);
}
} // namespace quite::proto
