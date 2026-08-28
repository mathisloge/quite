// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <optional>
#include <quite/client/remote_object.hpp>
#include <quite/error.hpp>

namespace quite::client::test
{
class FakeRemoteObject final : public RemoteObject
{
  public:
    FakeRemoteObject(ObjectId id, std::unordered_map<std::string, PropertyPtr> properties)
        : RemoteObject{id}
        , properties_{std::move(properties)}
    {}

    void set_fetch_properties_error(Error error)
    {
        fetch_properties_error_ = std::move(error);
    }

    void set_snapshot(Image image)
    {
        snapshot_ = std::move(image);
    }

    void set_take_snapshot_error(Error error)
    {
        take_snapshot_error_ = std::move(error);
    }

    meta::TypeId type_id() const override
    {
        return 0;
    }

    AsyncResult<std::unordered_map<std::string, PropertyPtr>> fetch_properties(
        std::vector<std::string> properties) override
    {
        if (fetch_properties_error_.has_value())
        {
            co_return std::unexpected(*fetch_properties_error_);
        }

        std::unordered_map<std::string, PropertyPtr> result;
        for (auto &&property_name : properties)
        {
            if (auto it = properties_.find(property_name); it != properties_.end())
            {
                result.emplace(it->first, it->second);
            }
        }
        co_return result;
    }

    AsyncResult<PropertyPtr> property(std::string property_name) override
    {
        if (auto it = properties_.find(property_name); it != properties_.end())
        {
            co_return it->second;
        }
        co_return make_error_result(ErrorCode::not_found, fmt::format("no such property: {}", property_name));
    }

    AsyncResult<void> write_property(std::string /*property_name*/, entt::meta_any /*value*/) override
    {
        co_return Result<void>{};
    }

    AsyncResult<void> mouse_action() override
    {
        co_return Result<void>{};
    }

    AsyncResult<Image> take_snapshot() override
    {
        if (take_snapshot_error_.has_value())
        {
            co_return std::unexpected(*take_snapshot_error_);
        }
        co_return snapshot_;
    }

    AsyncResult<entt::meta_any> invoke_method(std::string /*method_name*/,
                                              std::vector<entt::meta_any> /*parameters*/) override
    {
        co_return entt::meta_any{};
    }

  private:
    std::unordered_map<std::string, PropertyPtr> properties_;
    std::optional<Error> fetch_properties_error_;
    Image snapshot_;
    std::optional<Error> take_snapshot_error_;
};
} // namespace quite::client::test
