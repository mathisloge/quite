// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <format>
#include "quite/core/bit_flags.hpp"

template <typename T>
struct std::formatter<quite::BitFlags<T>>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return ctx.begin();
    }

    auto format(const quite::BitFlags<T> &bf, std::format_context &ctx) const
    {
        using underlying_t = std::underlying_type_t<T>;
        constexpr size_t kNumBits = sizeof(underlying_t) * 8;
        auto val = bf.to_raw();

        // Format as binary string
        std::string binary;
        binary.reserve(kNumBits);
        for (size_t i = 0; i < kNumBits; ++i)
        {
            binary = ((val & 1) ? '1' : '0') + binary;
            val >>= 1;
        }

        return std::format_to(ctx.out(), "{}", binary);
    }
};
