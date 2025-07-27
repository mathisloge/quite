// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <string>
#include <unordered_map>
#include <entt/meta/meta.hpp>
#include "quite/quite_core_export.hpp"

namespace quite
{
struct QUITE_CORE_EXPORT GenericClass
{
    using PropertyMap = std::unordered_map<std::string, entt::meta_any>;
    PropertyMap properties;
};
} // namespace quite
