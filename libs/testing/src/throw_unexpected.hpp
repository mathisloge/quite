// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <quite/result.hpp>
#include "quite/test/exceptions.hpp"
namespace quite::test
{
template <typename T>
constexpr void throw_unexpected(const Result<T> &result)
{
    if (not result.has_value())
    {
        throw RemoteException{result.error()};
    }
}
} // namespace quite::test
