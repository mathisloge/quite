// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <quite/client/remote_object.hpp>
namespace quite::client
{
RemoteObject::RemoteObject(ObjectId id)
    : id_{id}
{}

RemoteObject::~RemoteObject() = default;

ObjectId RemoteObject::id() const noexcept
{
    return id_;
}
} // namespace quite::client
