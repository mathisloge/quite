// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <concepts>

namespace quite
{
template <std::integral T = unsigned int>
constexpr T bit(std::size_t position)
{
    return static_cast<T>(1) << position;
}
} // namespace quite
