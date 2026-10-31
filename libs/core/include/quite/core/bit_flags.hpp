// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <initializer_list>
#include <type_traits>
namespace quite
{
template <typename T>
class BitFlags
{
    using underlying_t = std::underlying_type_t<T>;

  public:
    constexpr BitFlags()
        : flags_(static_cast<underlying_t>(0))
    {}

    constexpr explicit BitFlags(T v)
        : flags_(to_underlying(v))
    {}

    constexpr BitFlags(std::initializer_list<T> vs)
        : BitFlags()
    {
        for (T v : vs)
        {
            flags_ |= to_underlying(v);
        }
    }

    constexpr bool is_set(T v) const
    {
        return (flags_ & to_underlying(v)) == to_underlying(v);
    }

    constexpr void set(T v)
    {
        flags_ |= to_underlying(v);
    }

    constexpr void unset(T v)
    {
        flags_ &= ~to_underlying(v);
    }

    constexpr void clear()
    {
        flags_ = static_cast<underlying_t>(0);
    }

    constexpr operator bool() const
    {
        return flags_ != static_cast<underlying_t>(0);
    }

    friend constexpr BitFlags operator|(BitFlags lhs, T rhs)
    {
        return BitFlags(lhs.flags_ | to_underlying(rhs));
    }

    friend constexpr BitFlags operator|(BitFlags lhs, BitFlags rhs)
    {
        return BitFlags(lhs.flags_ | rhs.flags_);
    }

    friend constexpr BitFlags operator&(BitFlags lhs, T rhs)
    {
        return BitFlags(lhs.flags_ & to_underlying(rhs));
    }

    friend constexpr BitFlags operator&(BitFlags lhs, BitFlags rhs)
    {
        return BitFlags(lhs.flags_ & rhs.flags_);
    }

    friend constexpr BitFlags operator^(BitFlags lhs, T rhs)
    {
        return BitFlags(lhs.flags_ ^ to_underlying(rhs));
    }

    friend constexpr BitFlags operator^(BitFlags lhs, BitFlags rhs)
    {
        return BitFlags(lhs.flags_ ^ rhs.flags_);
    }

    friend constexpr BitFlags &operator|=(BitFlags &lhs, T rhs)
    {
        lhs.flags_ |= to_underlying(rhs);
        return lhs;
    }
    friend constexpr BitFlags &operator|=(BitFlags &lhs, BitFlags rhs)
    {
        lhs.flags_ |= rhs.flags_;
        return lhs;
    }
    friend constexpr BitFlags &operator&=(BitFlags &lhs, T rhs)
    {
        lhs.flags_ &= to_underlying(rhs);
        return lhs;
    }
    friend constexpr BitFlags &operator&=(BitFlags &lhs, BitFlags rhs)
    {
        lhs.flags_ &= rhs.flags_;
        return lhs;
    }
    friend constexpr BitFlags &operator^=(BitFlags &lhs, T rhs)
    {
        lhs.flags_ ^= to_underlying(rhs);
        return lhs;
    }
    friend constexpr BitFlags &operator^=(BitFlags &lhs, BitFlags rhs)
    {
        lhs.flags_ ^= rhs.flags_;
        return lhs;
    }

    friend constexpr BitFlags operator~(const BitFlags &bf)
    {
        return BitFlags(~bf.flags_);
    }

    friend constexpr bool operator==(const BitFlags &lhs, const BitFlags &rhs)
    {
        return lhs.flags_ == rhs.flags_;
    }

    friend constexpr bool operator!=(const BitFlags &lhs, const BitFlags &rhs)
    {
        return lhs.flags_ != rhs.flags_;
    }

    // Construct BitFlags from raw values.
    static constexpr BitFlags from_raw(underlying_t flags)
    {
        return BitFlags(flags);
    }

    // Retrieve the raw underlying flags.
    constexpr underlying_t to_raw() const
    {
        return flags_;
    }

  private:
    constexpr explicit BitFlags(underlying_t flags)
        : flags_(flags)
    {}
    static constexpr underlying_t to_underlying(T v)
    {
        return static_cast<underlying_t>(v);
    }
    underlying_t flags_;
};
} // namespace quite
