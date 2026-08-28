// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <quite/proto/probe/probe_handler.hpp>

namespace quite::proto::test
{
// Returns canned results for every IProbeHandler operation; used to drive a real Server/Client
// pair over an actual (local) gRPC transport without needing a real probe implementation.
class FakeProbeHandler final : public IProbeHandler
{
  public:
    AsyncResult<entt::meta_any> object_instance(ObjectId /*object_id*/) override
    {
        co_return entt::meta_any{};
    }

    AsyncResult<ImageData> take_snapshot(ObjectId /*object_id*/) override
    {
        co_return ImageData{};
    }

    AsyncResult<ObjectReference> find_object(ObjectQuery /*query*/) override
    {
        co_return ObjectReference{.object_id = 99, .type_id = 3};
    }

    AsyncResult<PropertyMap> fetch_properties(ObjectId /*object_id*/, std::vector<std::string> /*properties*/) override
    {
        co_return PropertyMap{};
    }

    AsyncResult<void> set_property(ObjectId /*object_id*/, std::string /*property*/, entt::meta_any /*value*/) override
    {
        co_return Result<void>{};
    }

    AsyncResult<std::vector<ObjectReference>> fetch_windows() override
    {
        co_return std::vector<ObjectReference>{};
    }

    AsyncResult<entt::meta_any> invoke_method(entt::meta_any /*object*/,
                                              std::string /*qualified_method_signature*/,
                                              std::vector<entt::meta_any> /*params*/) override
    {
        co_return entt::meta_any{};
    }
};
} // namespace quite::proto::test
