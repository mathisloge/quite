// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <entt/meta/meta.hpp>
#include "quite/test/property.hpp"

namespace quite::test
{
Property::Value convert_any(const entt::meta_any &value);
entt::meta_any convert_any(Property::Value value);
} // namespace quite::test
