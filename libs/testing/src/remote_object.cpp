// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "quite/test/remote_object.hpp"
#include <quite/client/remote_object.hpp>
#include "quite/test/property.hpp"
#include "throw_unexpected.hpp"
#include "value_convert.hpp"

namespace quite::test
{

RemoteObject::RemoteObject(std::shared_ptr<client::RemoteObject> object)
    : object_{std::move(object)}
{}

void RemoteObject::mouse_action()
{
    const auto [action_result] = stdexec::sync_wait(object_->mouse_action()).value();
    throw_unexpected(action_result);
}

Image RemoteObject::take_snapshot()
{
    auto [snapshot] = stdexec::sync_wait(object_->take_snapshot()).value();
    throw_unexpected(snapshot);
    return std::move(snapshot.value());
}

Property::Value RemoteObject::invoke_method(std::string method_name, std::vector<Property::Value> parameters)
{
    std::vector<entt::meta_any> any_parameters;
    any_parameters.reserve(parameters.size());
    std::ranges::transform(std::move(parameters), std::back_inserter(any_parameters), [](auto &&p) {
        return convert_any(std::forward<decltype(p)>(p));
    });

    const auto [invoke_result] =
        stdexec::sync_wait(object_->invoke_method(std::move(method_name), std::move(any_parameters))).value();
    throw_unexpected(invoke_result);
    return convert_any(invoke_result); // TODO: what happens with void?
}

Property RemoteObject::property(std::string name)
{
    auto [result] = stdexec::sync_wait(object_->property(std::move(name))).value();
    throw_unexpected(result);
    return Property{std::move(result.value())};
}

std::shared_ptr<client::RemoteObject> RemoteObject::underlying_object()
{
    return object_;
}

bool RemoteObject::operator==(const RemoteObject &rhs) const
{
    return this->object_ == rhs.object_;
}
} // namespace quite::test
