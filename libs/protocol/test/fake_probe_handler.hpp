// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <optional>
#include <quite/error.hpp>
#include <quite/proto/probe/probe_handler.hpp>
#include <quite/value/object_query.hpp>

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

    // When set, every operation returns this error instead of its configured canned result.
    void set_error(Error error)
    {
        error_ = std::move(error);
    }

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
        if (error_)
        {
            co_return std::unexpected(*error_);
        }
        co_return object_instance_;
    }

    AsyncResult<ImageData> take_snapshot(ObjectId /*object_id*/) override
    {
        if (error_)
        {
            co_return std::unexpected(*error_);
        }
        co_return snapshot_;
    }

    AsyncResult<ObjectReference> find_object(ObjectQuery query) override
    {
        if (error_)
        {
            co_return std::unexpected(*error_);
        }
        last_find_object_query_ = std::move(query);
        co_return ObjectReference{.object_id = 99, .type_id = 3};
    }

    AsyncResult<PropertyMap> fetch_properties(ObjectId /*object_id*/, std::vector<std::string> /*properties*/) override
    {
        if (error_)
        {
            co_return std::unexpected(*error_);
        }
        co_return properties_;
    }

    AsyncResult<void> set_property(ObjectId object_id, std::string property, entt::meta_any value) override
    {
        if (error_)
        {
            co_return std::unexpected(*error_);
        }
        last_set_property_call_ = SetPropertyCall{.object_id = object_id, .property = property, .value = value};
        co_return Result<void>{};
    }

    AsyncResult<std::vector<ObjectReference>> fetch_windows() override
    {
        if (error_)
        {
            co_return std::unexpected(*error_);
        }
        co_return windows_;
    }

    AsyncResult<entt::meta_any> invoke_method(entt::meta_any object,
                                              std::string qualified_method_signature,
                                              std::vector<entt::meta_any> params) override
    {
        if (error_)
        {
            co_return std::unexpected(*error_);
        }
        last_invoke_method_call_ = InvokeMethodCall{
            .object = object, .qualified_method_signature = qualified_method_signature, .params = params};
        co_return invoke_method_result_;
    }

    const std::optional<ObjectQuery> &last_find_object_query() const
    {
        return last_find_object_query_;
    }

  private:
    std::optional<Error> error_;
    entt::meta_any object_instance_;
    std::vector<ObjectReference> windows_;
    PropertyMap properties_;
    IProbeHandler::ImageData snapshot_;
    entt::meta_any invoke_method_result_;
    std::optional<SetPropertyCall> last_set_property_call_;
    std::optional<InvokeMethodCall> last_invoke_method_call_;
    std::optional<ObjectQuery> last_find_object_query_;
};
} // namespace quite::proto::test
