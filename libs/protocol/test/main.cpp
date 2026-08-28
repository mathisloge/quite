// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <gtest/gtest.h>
#include <quite/setup_logger.hpp>

int main(int argc, char *argv[])
{
    quite::setup_logger();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
