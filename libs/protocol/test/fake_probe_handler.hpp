// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <optional>
#include <quite/proto/probe/probe_handler.hpp>

namespace quite::proto::test
{
// Returns canned/configurable results for every IProbeHandler operation, and records the
// arguments of the last write-style call; used to drive a real Server/Client pair over an
// actual (local) gRPC transport without needing a real probe implementation.
class FakeProbeHandler final : public IProbeHandler
{
  public:
    struct SetPropertyCall
    {
        ObjectId object_id;
        std::string property;
        entt::meta_any value;
    };

    struct InvokeMethodCall
    {
        entt::meta_any object;
        std::string qualified_method_signature;
        std::vector<entt::meta_any> params;
    };

    void set_object_instance(entt::meta_any value)
    {
        object_instance_ = std::move(value);
    }

    void set_windows(std::vector<ObjectReference> windows)
    {
        windows_ = std::move(windows);
    }

    void set_properties(PropertyMap properties)
    {
        properties_ = std::move(properties);
    }

    void set_snapshot(ImageData image)
    {
        snapshot_ = std::move(image);
    }

    void set_invoke_method_result(entt::meta_any value)
    {
        invoke_method_result_ = std::move(value);
    }

    const std::optional<SetPropertyCall> &last_set_property_call() const
    {
        return last_set_property_call_;
    }

    const std::optional<InvokeMethodCall> &last_invoke_method_call() const
    {
        return last_invoke_method_call_;
    }

    AsyncResult<entt::meta_any> object_instance(ObjectId /*object_id*/) override
    {
        co_return object_instance_;
    }

    AsyncResult<ImageData> take_snapshot(ObjectId /*object_id*/) override
    {
        co_return snapshot_;
    }

    AsyncResult<ObjectReference> find_object(ObjectQuery /*query*/) override
    {
        co_return ObjectReference{.object_id = 99, .type_id = 3};
    }

    AsyncResult<PropertyMap> fetch_properties(ObjectId /*object_id*/, std::vector<std::string> /*properties*/) override
    {
        co_return properties_;
    }

    AsyncResult<void> set_property(ObjectId object_id, std::string property, entt::meta_any value) override
    {
        last_set_property_call_ = SetPropertyCall{.object_id = object_id, .property = property, .value = value};
        co_return Result<void>{};
    }

    AsyncResult<std::vector<ObjectReference>> fetch_windows() override
    {
        co_return windows_;
    }

    AsyncResult<entt::meta_any> invoke_method(entt::meta_any object,
                                              std::string qualified_method_signature,
                                              std::vector<entt::meta_any> params) override
    {
        last_invoke_method_call_ = InvokeMethodCall{
            .object = object, .qualified_method_signature = qualified_method_signature, .params = params};
        co_return invoke_method_result_;
    }

  private:
    entt::meta_any object_instance_;
    std::vector<ObjectReference> windows_;
    PropertyMap properties_;
    IProbeHandler::ImageData snapshot_;
    entt::meta_any invoke_method_result_;
    std::optional<SetPropertyCall> last_set_property_call_;
    std::optional<InvokeMethodCall> last_invoke_method_call_;
};
} // namespace quite::proto::test
