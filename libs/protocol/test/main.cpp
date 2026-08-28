// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <entt/locator/locator.hpp>
#include <gtest/gtest.h>
#include <quite/setup_logger.hpp>
#include <quite/value/value_registry.hpp>

int main(int argc, char *argv[])
{
    quite::setup_logger();
    entt::locator<quite::ValueRegistry>::emplace();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
