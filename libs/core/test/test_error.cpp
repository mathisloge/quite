// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <gtest/gtest.h>
#include <quite/error.hpp>

using namespace quite;

TEST(CoreError, Formatting)
{
    const quite::Error error{
        .code = quite::ErrorCode::deadline_exceeded,
        .message = "test message",
    };
    EXPECT_EQ("(error_code: deadline_exceeded: message: test message)", fmt::format("{}", error));
}
