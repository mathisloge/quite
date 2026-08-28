// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <quite/client/utils/dump_properties.hpp>
#include <quite/value/generic_value_class.hpp>
#include "fakes/fake_property.hpp"
#include "fakes/fake_remote_object.hpp"

using namespace quite;
using namespace quite::client;
using namespace quite::client::test;

namespace
{
Result<nlohmann::json> run_dump_properties(RemoteObjectPtr object, std::vector<std::string> properties)
{
    auto [result] = stdexec::sync_wait(dump_properties(std::move(object), std::move(properties))).value();
    return result;
}
} // namespace

TEST(DumpProperties, IncludesRequestedGenericClassProperty)
{
    GenericClass generic{.properties = {{"nested", entt::meta_any{std::int32_t{42}}}}};
    auto property = std::make_shared<FakeProperty>("shape", Result<entt::meta_any>{entt::meta_any{std::move(generic)}});
    auto object = std::make_shared<FakeRemoteObject>(
        1, std::unordered_map<std::string, PropertyPtr>{{"shape", std::move(property)}});

    const auto result = run_dump_properties(object, {"shape"});

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->contains("shape"));
}

TEST(DumpProperties, PropagatesFetchPropertiesError)
{
    auto object = std::make_shared<FakeRemoteObject>(1, std::unordered_map<std::string, PropertyPtr>{});
    object->set_fetch_properties_error(Error{.code = ErrorCode::not_found, .message = "missing"});

    const auto result = run_dump_properties(object, {"shape"});

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::not_found);
}

TEST(DumpProperties, PropertyWithoutValueBecomesNullJson)
{
    auto property = std::make_shared<FakeProperty>(
        "broken", Result<entt::meta_any>{std::unexpected(Error{.code = ErrorCode::unknown, .message = "no value"})});
    auto object = std::make_shared<FakeRemoteObject>(
        1, std::unordered_map<std::string, PropertyPtr>{{"broken", std::move(property)}});

    const auto result = run_dump_properties(object, {"broken"});

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE((*result)["broken"].is_null());
}

TEST(DumpProperties, OnlyRequestedPropertiesAreIncluded)
{
    auto shape = std::make_shared<FakeProperty>("shape", Result<entt::meta_any>{entt::meta_any{std::int32_t{1}}});
    auto color = std::make_shared<FakeProperty>("color", Result<entt::meta_any>{entt::meta_any{std::int32_t{2}}});
    auto object = std::make_shared<FakeRemoteObject>(
        1, std::unordered_map<std::string, PropertyPtr>{{"shape", std::move(shape)}, {"color", std::move(color)}});

    const auto result = run_dump_properties(object, {"shape"});

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->contains("shape"));
    EXPECT_FALSE(result->contains("color"));
}
