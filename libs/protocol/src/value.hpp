// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <entt/meta/meta.hpp>
#include <quite/value/value_registry.hpp>
#include "quite/proto/client/value_converter.hpp"
#include "quite/proto/types.pb.h"

namespace quite::proto
{
Value create_value(const ValueRegistry &value_registry, const entt::meta_any &type);
entt::meta_any convert_value(const ValueRegistry &value_registry, const IValueConverter &converter, const Value &value);
} // namespace quite::proto
