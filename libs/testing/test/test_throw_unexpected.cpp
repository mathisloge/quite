// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <gtest/gtest.h>
#include <quite/test/exceptions.hpp>
#include "throw_unexpected.hpp"

namespace quite::test
{

TEST(ThrowUnexpected, DoesNotThrowOnSuccess)
{
    const Result<int> result{42};
    EXPECT_NO_THROW(throw_unexpected(result));
}

TEST(ThrowUnexpected, ThrowsRemoteExceptionOnError)
{
    const Result<int> result = std::unexpected(Error{.code = ErrorCode::not_found, .message = "missing"});
    EXPECT_THROW(throw_unexpected(result), RemoteException);
}
} // namespace quite::test
