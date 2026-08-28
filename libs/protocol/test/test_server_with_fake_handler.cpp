// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <atomic>
#include <optional>
#include <fmt/format.h>
#include <gtest/gtest.h>
#include <quite/proto/client/client.hpp>
#include <quite/proto/client/probe_client.hpp>
#include <quite/proto/client/value_converter.hpp>
#include <quite/proto/probe/server.hpp>
#include <quite/value/value_registry.hpp>
#include <unistd.h>
#include "fake_meta_registry.hpp"
#include "fake_mouse_injector.hpp"
#include "fake_probe_handler.hpp"

using namespace quite;
using namespace quite::proto;
using namespace quite::proto::test;

namespace
{
std::string unique_socket_url()
{
    static std::atomic<int> counter{0};
    return fmt::format("unix:///tmp/quite_test_fake_handler_{}_{}.sock", getpid(), counter++);
}

class NullValueConverter final : public IValueConverter
{
  public:
    entt::meta_any from(ObjectReference /*ref*/) const override
    {
        return {};
    }
};

class ProbeRoundTripTest : public ::testing::Test
{
  protected:
    void connect(ServiceHandle<IProbeHandler> probe_handler = {},
                 ServiceHandle<core::IMouseInjector> mouse_injector = {},
                 ServiceHandle<meta::MetaRegistry> meta_registry = {})
    {
        const auto url = unique_socket_url();
        server_.emplace(url,
                        std::move(probe_handler),
                        std::move(mouse_injector),
                        std::move(meta_registry),
                        ServiceHandle<ValueRegistry>{std::make_shared<ValueRegistry>()});

        entt::locator<ValueRegistry>::emplace();
        client_.emplace(entt::locator<ValueRegistry>::handle());
        probe_client_ = client_->create_probe_client(std::make_shared<NullValueConverter>(), url);

        auto [connected] = stdexec::sync_wait(probe_client_->wait_for_connected(std::chrono::seconds(5))).value();
        ASSERT_TRUE(connected.has_value());
    }

    std::optional<Server> server_;
    std::optional<Client> client_;
    std::shared_ptr<ProbeClient> probe_client_;
};
} // namespace

TEST_F(ProbeRoundTripTest, FindObjectRoundTripsThroughRealTransport)
{
    connect(ServiceHandle<IProbeHandler>{std::make_shared<FakeProbeHandler>()});

    auto [result] = stdexec::sync_wait(probe_client_->probe_service().find_object(ObjectQuery{})).value();

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->object_id, 99u);
    EXPECT_EQ(result->type_id, 3u);
}

TEST_F(ProbeRoundTripTest, FetchWindowsRoundTripsThroughRealTransport)
{
    auto handler = std::make_shared<FakeProbeHandler>();
    handler->set_windows(
        {ObjectReference{.object_id = 1, .type_id = 10}, ObjectReference{.object_id = 2, .type_id = 20}});
    connect(ServiceHandle<IProbeHandler>{handler});

    auto [result] = stdexec::sync_wait(probe_client_->probe_service().query_top_level_views()).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result->size(), 2u);
    EXPECT_EQ((*result)[0].object_id, 1u);
    EXPECT_EQ((*result)[0].type_id, 10u);
    EXPECT_EQ((*result)[1].object_id, 2u);
    EXPECT_EQ((*result)[1].type_id, 20u);
}

TEST_F(ProbeRoundTripTest, GetObjectPropertiesRoundTripsThroughRealTransport)
{
    auto handler = std::make_shared<FakeProbeHandler>();
    IProbeHandler::PropertyMap properties;
    properties.emplace("answer", entt::meta_any{std::int64_t{42}});
    handler->set_properties(std::move(properties));
    connect(ServiceHandle<IProbeHandler>{handler});

    auto [result] = stdexec::sync_wait(probe_client_->probe_service().get_object_properties(1, {"answer"})).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(result->contains("answer"));
    EXPECT_EQ(result->at("answer").cast<std::int64_t>(), 42);
}

TEST_F(ProbeRoundTripTest, SetObjectPropertyRoundTripsThroughRealTransport)
{
    auto handler = std::make_shared<FakeProbeHandler>();
    connect(ServiceHandle<IProbeHandler>{handler});

    auto [result] = stdexec::sync_wait(probe_client_->probe_service().set_object_property(
                                           7, "name", entt::meta_any{std::string{"hello"}}))
                        .value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(handler->last_set_property_call().has_value());
    EXPECT_EQ(handler->last_set_property_call()->object_id, 7u);
    EXPECT_EQ(handler->last_set_property_call()->property, "name");
    ASSERT_TRUE(handler->last_set_property_call()->value.allow_cast<std::string>());
    EXPECT_EQ(handler->last_set_property_call()->value.cast<std::string>(), "hello");
}

TEST_F(ProbeRoundTripTest, InvokeMethodRoundTripsThroughRealTransport)
{
    auto handler = std::make_shared<FakeProbeHandler>();
    handler->set_object_instance(entt::meta_any{std::int64_t{123}});
    handler->set_invoke_method_result(entt::meta_any{std::int64_t{55}});
    connect(ServiceHandle<IProbeHandler>{handler});

    std::vector<entt::meta_any> params{entt::meta_any{std::int64_t{5}}};
    auto [result] = stdexec::sync_wait(probe_client_->probe_service().invoke_method(1, "add(int)", params)).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(result->allow_cast<std::int64_t>());
    EXPECT_EQ(result->cast<std::int64_t>(), 55);

    ASSERT_TRUE(handler->last_invoke_method_call().has_value());
    const auto &call = *handler->last_invoke_method_call();
    ASSERT_TRUE(call.object.allow_cast<std::int64_t>());
    EXPECT_EQ(call.object.cast<std::int64_t>(), 123);
    EXPECT_EQ(call.qualified_method_signature, "add(int)");
    ASSERT_EQ(call.params.size(), 1u);
    ASSERT_TRUE(call.params[0].allow_cast<std::int64_t>());
    EXPECT_EQ(call.params[0].cast<std::int64_t>(), 5);
}

TEST_F(ProbeRoundTripTest, TakeSnapshotRoundTripsThroughRealTransport)
{
    auto handler = std::make_shared<FakeProbeHandler>();
    handler->set_snapshot(IProbeHandler::ImageData{.width = 2, .height = 1, .image_data = {'a', 'b'}});
    connect(ServiceHandle<IProbeHandler>{handler});

    auto [result] = stdexec::sync_wait(probe_client_->probe_service().take_snapshot(1)).value();

    ASSERT_TRUE(result.has_value());
    const auto image_data = result->data();
    EXPECT_EQ(image_data.width, 2u);
    EXPECT_EQ(image_data.height, 1u);
    ASSERT_EQ(image_data.data.size(), 2u);
    EXPECT_EQ(static_cast<char>(image_data.data[0]), 'a');
    EXPECT_EQ(static_cast<char>(image_data.data[1]), 'b');
}

TEST_F(ProbeRoundTripTest, MouseActionRoundTripsThroughRealTransport)
{
    auto mouse_injector = std::make_shared<FakeMouseInjector>();
    connect({}, ServiceHandle<core::IMouseInjector>{mouse_injector});

    core::MouseAction action{.position = {1.0, 2.0},
                             .button = core::MouseButton::left,
                             .trigger = core::MouseTrigger::click,
                             .modifier = core::KeyboardModifier::none};
    auto [result] = stdexec::sync_wait(probe_client_->mouse_injector().single_action(42, action)).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(mouse_injector->last_call().has_value());
    EXPECT_EQ(mouse_injector->last_call()->target_id, 42u);
    EXPECT_EQ(mouse_injector->last_call()->action.trigger, core::MouseTrigger::click);
}

TEST_F(ProbeRoundTripTest, FindObjectWithNestedQueryRoundTripsThroughRealTransport)
{
    auto handler = std::make_shared<FakeProbeHandler>();
    connect(ServiceHandle<IProbeHandler>{handler});

    auto parent_query = std::make_shared<ObjectQuery>();
    parent_query->type_name = "Window";
    parent_query->properties = {{"title", entt::meta_any{std::string{"main"}}}};

    ObjectQuery query;
    query.type_name = "Button";
    query.container = parent_query;
    query.properties = {{"text", entt::meta_any{std::string{"OK"}}}};

    auto [result] = stdexec::sync_wait(probe_client_->probe_service().find_object(query)).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(handler->last_find_object_query().has_value());
    const auto &received = *handler->last_find_object_query();
    EXPECT_EQ(received.type_name, "Button");
    ASSERT_TRUE(received.properties.contains("text"));
    EXPECT_EQ(received.properties.at("text").cast<std::string>(), "OK");
    ASSERT_NE(received.container, nullptr);
    ASSERT_TRUE(received.container->properties.contains("title"));
    EXPECT_EQ(received.container->properties.at("title").cast<std::string>(), "main");
}

// Regression test for a bug where the server-side parent-chain walk in rpc_find_object.cpp
// re-read the top-level query's immediate parent on every loop iteration instead of advancing
// to parent->parent(), causing an infinite loop for any query nested two or more levels deep.
TEST_F(ProbeRoundTripTest, FindObjectWithGrandparentQueryRoundTripsThroughRealTransport)
{
    auto handler = std::make_shared<FakeProbeHandler>();
    connect(ServiceHandle<IProbeHandler>{handler});

    auto grandparent_query = std::make_shared<ObjectQuery>();
    grandparent_query->type_name = "MainWindow";
    grandparent_query->properties = {{"title", entt::meta_any{std::string{"app"}}}};

    auto parent_query = std::make_shared<ObjectQuery>();
    parent_query->type_name = "Panel";
    parent_query->container = grandparent_query;
    parent_query->properties = {{"name", entt::meta_any{std::string{"toolbar"}}}};

    ObjectQuery query;
    query.type_name = "Button";
    query.container = parent_query;
    query.properties = {{"text", entt::meta_any{std::string{"OK"}}}};

    auto [result] = stdexec::sync_wait(probe_client_->probe_service().find_object(query)).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(handler->last_find_object_query().has_value());
    const auto &received = *handler->last_find_object_query();
    EXPECT_EQ(received.type_name, "Button");
    ASSERT_TRUE(received.properties.contains("text"));
    EXPECT_EQ(received.properties.at("text").cast<std::string>(), "OK");

    ASSERT_NE(received.container, nullptr);
    ASSERT_TRUE(received.container->properties.contains("name"));
    EXPECT_EQ(received.container->properties.at("name").cast<std::string>(), "toolbar");

    ASSERT_NE(received.container->container, nullptr);
    ASSERT_TRUE(received.container->container->properties.contains("title"));
    EXPECT_EQ(received.container->container->properties.at("title").cast<std::string>(), "app");
    EXPECT_EQ(received.container->container->container, nullptr);
}

TEST_F(ProbeRoundTripTest, MetaFindTypeReturnsPrimitiveType)
{
    auto meta_registry =
        std::make_shared<FakeMetaRegistry>(Result<meta::Type>{meta::Type{meta::PrimitiveType::type_double}});
    connect({}, {}, ServiceHandle<meta::MetaRegistry>{meta_registry});

    auto [result] = stdexec::sync_wait(probe_client_->meta_registry().lookup_type(1)).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(std::holds_alternative<meta::PrimitiveType>(*result));
    EXPECT_EQ(std::get<meta::PrimitiveType>(*result), meta::PrimitiveType::type_double);
}

TEST_F(ProbeRoundTripTest, MetaFindTypeReturnsListType)
{
    meta::ListType list{.id = 5, .name = "IntList", .value_type = 2};
    auto meta_registry = std::make_shared<FakeMetaRegistry>(Result<meta::Type>{meta::Type{list}});
    connect({}, {}, ServiceHandle<meta::MetaRegistry>{meta_registry});

    auto [result] = stdexec::sync_wait(probe_client_->meta_registry().lookup_type(5)).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(std::holds_alternative<meta::ListType>(*result));
    const auto &received = std::get<meta::ListType>(*result);
    EXPECT_EQ(received.id, 5u);
    EXPECT_EQ(received.name, "IntList");
    EXPECT_EQ(received.value_type, 2u);
}

TEST_F(ProbeRoundTripTest, MetaFindTypeReturnsMapType)
{
    meta::MapType map{.id = 6, .name = "Dict", .key_type = 1, .value_type = 2};
    auto meta_registry = std::make_shared<FakeMetaRegistry>(Result<meta::Type>{meta::Type{map}});
    connect({}, {}, ServiceHandle<meta::MetaRegistry>{meta_registry});

    auto [result] = stdexec::sync_wait(probe_client_->meta_registry().lookup_type(6)).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(std::holds_alternative<meta::MapType>(*result));
    const auto &received = std::get<meta::MapType>(*result);
    EXPECT_EQ(received.id, 6u);
    EXPECT_EQ(received.name, "Dict");
    EXPECT_EQ(received.key_type, 1u);
    EXPECT_EQ(received.value_type, 2u);
}

TEST_F(ProbeRoundTripTest, MetaFindTypeReturnsEnumType)
{
    auto enum_type = std::make_unique<meta::EnumType>();
    enum_type->id = 7;
    enum_type->name = "Color";
    enum_type->values = {{"Red", 0}, {"Green", 1}};
    auto meta_registry = std::make_shared<FakeMetaRegistry>(Result<meta::Type>{meta::Type{std::move(enum_type)}});
    connect({}, {}, ServiceHandle<meta::MetaRegistry>{meta_registry});

    auto [result] = stdexec::sync_wait(probe_client_->meta_registry().lookup_type(7)).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(std::holds_alternative<meta::EnumTypePtr>(*result));
    const auto &received = *std::get<meta::EnumTypePtr>(*result);
    EXPECT_EQ(received.id, 7u);
    EXPECT_EQ(received.name, "Color");
    ASSERT_EQ(received.values.size(), 2u);
    EXPECT_EQ(received.values.at("Red"), 0);
    EXPECT_EQ(received.values.at("Green"), 1);
}

TEST_F(ProbeRoundTripTest, MetaFindTypeReturnsObjectType)
{
    auto object_type = std::make_unique<meta::ObjectType>();
    object_type->id = 8;
    object_type->name = "Widget";
    object_type->properties = {meta::Property{.name = "x", .type = 2}};
    auto meta_registry = std::make_shared<FakeMetaRegistry>(Result<meta::Type>{meta::Type{std::move(object_type)}});
    connect({}, {}, ServiceHandle<meta::MetaRegistry>{meta_registry});

    auto [result] = stdexec::sync_wait(probe_client_->meta_registry().lookup_type(8)).value();

    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(std::holds_alternative<meta::ObjectTypePtr>(*result));
    const auto &received = *std::get<meta::ObjectTypePtr>(*result);
    EXPECT_EQ(received.id, 8u);
    EXPECT_EQ(received.name, "Widget");
    ASSERT_EQ(received.properties.size(), 1u);
    EXPECT_EQ(received.properties[0].name, "x");
    EXPECT_EQ(received.properties[0].type, 2u);
}

TEST_F(ProbeRoundTripTest, WaitForConnectedTimesOutWhenNothingListens)
{
    // No Server is started; nothing listens on this socket.
    const auto url = unique_socket_url();
    entt::locator<ValueRegistry>::emplace();
    client_.emplace(entt::locator<ValueRegistry>::handle());
    probe_client_ = client_->create_probe_client(std::make_shared<NullValueConverter>(), url);

    auto [connected] = stdexec::sync_wait(probe_client_->wait_for_connected(std::chrono::seconds(1))).value();

    ASSERT_FALSE(connected.has_value());
    EXPECT_EQ(connected.error().code, ErrorCode::deadline_exceeded);
}

TEST_F(ProbeRoundTripTest, FindObjectPropagatesErrorThroughRealTransport)
{
    auto handler = std::make_shared<FakeProbeHandler>();
    handler->set_error(Error{.code = ErrorCode::cancelled, .message = "cancelled by user"});
    connect(ServiceHandle<IProbeHandler>{handler});

    auto [result] = stdexec::sync_wait(probe_client_->probe_service().find_object(ObjectQuery{})).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::cancelled);
}

TEST_F(ProbeRoundTripTest, FetchWindowsPropagatesErrorThroughRealTransport)
{
    auto handler = std::make_shared<FakeProbeHandler>();
    handler->set_error(Error{.code = ErrorCode::unimplemented, .message = "not supported"});
    connect(ServiceHandle<IProbeHandler>{handler});

    auto [result] = stdexec::sync_wait(probe_client_->probe_service().query_top_level_views()).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::unimplemented);
}

TEST_F(ProbeRoundTripTest, GetObjectPropertiesPropagatesErrorThroughRealTransport)
{
    auto handler = std::make_shared<FakeProbeHandler>();
    handler->set_error(Error{.code = ErrorCode::deadline_exceeded, .message = "too slow"});
    connect(ServiceHandle<IProbeHandler>{handler});

    auto [result] = stdexec::sync_wait(probe_client_->probe_service().get_object_properties(1, {"answer"})).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::deadline_exceeded);
}

TEST_F(ProbeRoundTripTest, SetObjectPropertyPropagatesErrorThroughRealTransport)
{
    auto handler = std::make_shared<FakeProbeHandler>();
    handler->set_error(Error{.code = ErrorCode::aborted, .message = "conflict"});
    connect(ServiceHandle<IProbeHandler>{handler});

    auto [result] = stdexec::sync_wait(probe_client_->probe_service().set_object_property(
                                           7, "name", entt::meta_any{std::string{"hello"}}))
                        .value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::aborted);
}

TEST_F(ProbeRoundTripTest, InvokeMethodPropagatesErrorThroughRealTransport)
{
    auto handler = std::make_shared<FakeProbeHandler>();
    handler->set_error(Error{.code = ErrorCode::invalid_argument, .message = "bad args"});
    connect(ServiceHandle<IProbeHandler>{handler});

    auto [result] = stdexec::sync_wait(probe_client_->probe_service().invoke_method(1, "add(int)", {})).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::invalid_argument);
}

TEST_F(ProbeRoundTripTest, TakeSnapshotPropagatesErrorThroughRealTransport)
{
    auto handler = std::make_shared<FakeProbeHandler>();
    handler->set_error(Error{.code = ErrorCode::unavailable, .message = "no display"});
    connect(ServiceHandle<IProbeHandler>{handler});

    auto [result] = stdexec::sync_wait(probe_client_->probe_service().take_snapshot(1)).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::unavailable);
}

TEST_F(ProbeRoundTripTest, MouseActionPropagatesErrorThroughRealTransport)
{
    auto mouse_injector = std::make_shared<FakeMouseInjector>();
    mouse_injector->set_error(Error{.code = ErrorCode::failed_precondition, .message = "no window focused"});
    connect({}, ServiceHandle<core::IMouseInjector>{mouse_injector});

    core::MouseAction action{.position = {1.0, 2.0},
                             .button = core::MouseButton::left,
                             .trigger = core::MouseTrigger::click,
                             .modifier = core::KeyboardModifier::none};
    auto [result] = stdexec::sync_wait(probe_client_->mouse_injector().single_action(42, action)).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::failed_precondition);
}

TEST_F(ProbeRoundTripTest, MetaFindTypePropagatesErrorThroughRealTransport)
{
    auto meta_registry = std::make_shared<FakeMetaRegistry>(
        Result<meta::Type>{std::unexpected(Error{.code = ErrorCode::not_found, .message = "unknown type"})});
    connect({}, {}, ServiceHandle<meta::MetaRegistry>{meta_registry});

    auto [result] = stdexec::sync_wait(probe_client_->meta_registry().lookup_type(1)).value();

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::not_found);
}
