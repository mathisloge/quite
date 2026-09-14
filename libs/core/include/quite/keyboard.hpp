// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include "quite/core/bit.hpp"

namespace quite
{
enum class KeyboardModifier
{
    none = 0,
    shift = bit(0),
    control = bit(1),
    alt = bit(2),
    meta = bit(3),
};
} // namespace quite
