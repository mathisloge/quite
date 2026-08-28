// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <fmt/format.h>
#include <gtest/gtest.h>
#include <quite/asio_context.hpp>
#include <quite/manager/process.hpp>
#include <quite/manager/process_manager.hpp>
#include <quite/setup_logger.hpp>
#include "runnable_path.hpp"

using namespace quite::manager;
using namespace std::literals;

namespace
{
const bool kLoggerInitialized = [] {
    quite::setup_logger();
    return true;
}();
} // namespace

TEST(ProcessManager, NonProbeProcessFromEnvironmentCanBeLaunched)
{
    ProcessManager manager{quite::get_executor()};

    auto [exe] = stdexec::sync_wait(manager.find_executable({"ls"})).value();
    EXPECT_TRUE(exe.has_value());

    auto launch_result = exe.and_then([&](auto &&path) {
        return std::get<0>(stdexec::sync_wait(manager.launch_application({"ls"}, path, {"-a", "."}, {})).value());
    });

    EXPECT_TRUE(launch_result.has_value());

    if (launch_result.has_value())
    {
        auto [exit_code] = stdexec::sync_wait(launch_result.value()->async_wait_exit()).value();
        EXPECT_TRUE(exit_code.has_value());
        EXPECT_EQ(exit_code.value(), EXIT_SUCCESS);
    }
}

TEST(ProcessManager, NonProbeProcessCanBeLaunched)
{
    ProcessManager manager{quite::get_executor()};

    auto [process] = stdexec::sync_wait(manager.launch_application({"runnable"}, kRunnablePath, {}, {})).value();
    EXPECT_TRUE(process.has_value());

    if (process.has_value())
    {
        auto [exit_code] = stdexec::sync_wait(process.value()->async_wait_exit()).value();
        EXPECT_TRUE(exit_code.has_value());
        EXPECT_EQ(exit_code.value(), EXIT_SUCCESS);

        auto [runnable] = stdexec::sync_wait(manager.application({"runnable"})).value();
        EXPECT_TRUE(runnable.has_value());
        if (runnable.has_value())
        {
            EXPECT_EQ(runnable.value()->exit_code(), EXIT_SUCCESS);
        }
    }
}

TEST(ProcessManager, NonProbeProcessCanBeLaunchedWithArgs)
{
    ProcessManager manager{quite::get_executor()};

    auto [process] =
        stdexec::sync_wait(manager.launch_application({"runnable"}, kRunnablePath, {"--exit-code", "10"}, {})).value();
    EXPECT_TRUE(process.has_value());

    if (process.has_value())
    {
        auto [exit_code] = stdexec::sync_wait(process.value()->async_wait_exit()).value();
        EXPECT_TRUE(exit_code.has_value());
        EXPECT_EQ(exit_code.value(), 10);
    }
}

TEST(ProcessManager, NonProbeProcessCanBeLaunchedWithCustomEnvironment)
{
    ProcessManager manager{quite::get_executor()};

    auto [process] =
        stdexec::sync_wait(manager.launch_application({"runnable"}, kRunnablePath, {}, {{"TEST_EXIT_CODE", "20"}}))
            .value();
    EXPECT_TRUE(process.has_value());

    if (process.has_value())
    {
        auto [exit_code] = stdexec::sync_wait(process.value()->async_wait_exit()).value();
        EXPECT_TRUE(exit_code.has_value());
        EXPECT_EQ(exit_code.value(), 20);
    }
}

TEST(ProcessManager, NonProbeProcessCanBeLaunchedMultipleTimes)
{
    ProcessManager manager{quite::get_executor()};

    for (int i = 0; i < 2; ++i)
    {
        const auto expected_exit_code = i + 42;
        auto [process] =
            stdexec::sync_wait(
                manager.launch_application(
                    {"runnable"}, kRunnablePath, {"--exit-code", fmt::format("{}", expected_exit_code)}, {}))
                .value();

        EXPECT_TRUE(process.has_value());
        if (process.has_value())
        {
            auto [exit_code] = stdexec::sync_wait(process.value()->async_wait_exit()).value();
            EXPECT_TRUE(exit_code.has_value());
            EXPECT_EQ(exit_code.value(), expected_exit_code);

            auto [runnable] = stdexec::sync_wait(manager.application({"runnable"})).value();
            EXPECT_TRUE(runnable.has_value());
            if (runnable.has_value())
            {
                EXPECT_EQ(runnable.value()->exit_code(), expected_exit_code);
            }
        }
    }
}

TEST(ProcessManager, InvalidProcessWillNotCrash)
{
    ProcessManager manager{quite::get_executor()};

    auto [process] =
        stdexec::sync_wait(
            manager.launch_application({"not-found"}, "quite-not-found-program-42", {}, {{"TEST_EXIT_CODE", "42"}}))
            .value();

    EXPECT_FALSE(process.has_value());
}
