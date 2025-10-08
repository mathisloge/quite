// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <boost/ut.hpp>
#include <fmt/format.h>
#include <quite/asio_context.hpp>
#include <quite/manager/process.hpp>
#include <quite/manager/process_manager.hpp>
#include <quite/setup_logger.hpp>
#include "runnable_path.hpp"

using namespace boost::ut;
using namespace quite::manager;
using namespace std::literals;

static suite<"ProcessManager"> _ = [] {
    quite::setup_logger();

    "A non probe process from environment can be launched"_test = [] {
        ProcessManager manager{quite::get_executor()};

        auto [exe] = stdexec::sync_wait(manager.find_executable({"ls"})).value();
        expect(exe.has_value());

        auto launch_result = exe.and_then([&](auto &&path) {
            return std::get<0>(stdexec::sync_wait(manager.launch_application({"ls"}, path, {"-a", "."}, {})).value());
        });

        expect(launch_result.has_value());

        if (launch_result.has_value())
        {
            auto [exit_code] = stdexec::sync_wait(launch_result.value()->async_wait_exit()).value();
            expect(exit_code.has_value());
            expect(exit_code.value() == EXIT_SUCCESS);
        }
    };

    "A non probe process can be launched"_test = [] {
        ProcessManager manager{quite::get_executor()};

        auto [process] = stdexec::sync_wait(manager.launch_application({"runnable"}, kRunnablePath, {}, {})).value();
        expect(process.has_value());

        if (process.has_value())
        {
            auto [exit_code] = stdexec::sync_wait(process.value()->async_wait_exit()).value();
            expect(exit_code.has_value());
            expect(exit_code.value() == EXIT_SUCCESS);

            auto [runnable] = stdexec::sync_wait(manager.application({"runnable"})).value();
            expect(runnable.has_value());
            if (runnable.has_value())
            {
                expect(runnable.value()->exit_code() == EXIT_SUCCESS);
            }
        }
    };

    "A non probe process can be launched with args"_test = [] {
        ProcessManager manager{quite::get_executor()};

        auto [process] =
            stdexec::sync_wait(manager.launch_application({"runnable"}, kRunnablePath, {"--exit-code", "10"}, {}))
                .value();
        expect(process.has_value());

        if (process.has_value())
        {
            auto [exit_code] = stdexec::sync_wait(process.value()->async_wait_exit()).value();
            expect(exit_code.has_value());
            expect(exit_code.value() == 10);
        }
    };

    "A non probe process can be launched with a custom environment"_test = [] {
        ProcessManager manager{quite::get_executor()};

        auto [process] =
            stdexec::sync_wait(manager.launch_application({"runnable"}, kRunnablePath, {}, {{"TEST_EXIT_CODE", "20"}}))
                .value();
        expect(process.has_value());

        if (process.has_value())
        {
            auto [exit_code] = stdexec::sync_wait(process.value()->async_wait_exit()).value();
            expect(exit_code.has_value());
            expect(exit_code.value() == 20);
        }
    };

    "A non probe process can be launched multiple times"_test = [] {
        ProcessManager manager{quite::get_executor()};

        for (int i = 0; i < 2; ++i)
        {
            const auto expected_exit_code = i + 42;
            auto [process] =
                stdexec::sync_wait(
                    manager.launch_application(
                        {"runnable"}, kRunnablePath, {"--exit-code", fmt::format("{}", expected_exit_code)}, {}))
                    .value();

            expect(process.has_value());
            if (process.has_value())
            {
                auto [exit_code] = stdexec::sync_wait(process.value()->async_wait_exit()).value();
                expect(exit_code.has_value());
                expect(exit_code.value() == expected_exit_code);

                auto [runnable] = stdexec::sync_wait(manager.application({"runnable"})).value();
                expect(runnable.has_value());
                if (runnable.has_value())
                {
                    expect(runnable.value()->exit_code() == expected_exit_code);
                }
            }
        }
    };

    "An invalid process will not crash"_test = [] {
        ProcessManager manager{quite::get_executor()};

        auto [process] =
            stdexec::sync_wait(
                manager.launch_application({"not-found"}, "quite-not-found-program-42", {}, {{"TEST_EXIT_CODE", "42"}}))
                .value();

        expect(!process.has_value());
    };
};
