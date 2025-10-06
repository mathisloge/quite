// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
namespace quite
{
enum class MouseTrigger
{
    none,
    click,
    double_click,
    press,
    release,
    move
};

enum class MouseButton
{
    none,
    left,
    right,
    middle,
    forward,
    back,
};
} // namespace quite
