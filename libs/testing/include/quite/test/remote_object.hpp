// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <memory>
#include <quite/image.hpp>
#include "property.hpp"
#include "quite/quite_test_export.hpp"

namespace quite
{
namespace client
{
class RemoteObject;
}

namespace test
{
class QUITE_TEST_EXPORT RemoteObject
{
  public:
    explicit RemoteObject(std::shared_ptr<client::RemoteObject> object);

    void mouse_action();
    Property::Value invoke_method(std::string method_name, std::vector<Property::Value> parameters = {});
    [[nodiscard]] Image take_snapshot();
    [[nodiscard]] Property property(std::string name);

    [[nodiscard]] bool operator==(const RemoteObject &rhs) const;

    std::shared_ptr<client::RemoteObject> underlying_object();

  private:
    std::shared_ptr<client::RemoteObject> object_;
};
} // namespace test
} // namespace quite
