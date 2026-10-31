// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include "quite/core/bit_flags.hpp"
#include "quite/geometry.hpp"
#include "quite/keyboard.hpp"
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

struct MouseEventOptions
{
    Vector2 position = {};
    BitFlags<KeyboardModifier> modifiers = {KeyboardModifier::none};
};
} // namespace quite
