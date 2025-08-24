// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
namespace quite
{
class ValueRegistry;
}
namespace quite::probe
{
void register_converters(ValueRegistry &value_registry);
} // namespace quite::probe
