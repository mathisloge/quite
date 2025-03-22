#include <catch2/catch_test_macros.hpp>
#include <quite/manager/process.hpp>
#include <quite/manager/process_manager.hpp>
#include <quite/setup_logger.hpp>
#include "runnable_path.hpp"

using namespace quite::manager;

TEST_CASE("Test ProcessManager", "[manager]")
{
    quite::setup_logger();
    asio2exec::asio_context ctx;
    ctx.start();
    ProcessManager manager{ctx};

    SECTION("A non probe process from environment can be launched")
    {
        REQUIRE(ProcessManager::find_executable("ls")
                    .and_then([&](auto &&path) { return manager.launch_application("ls", path, {"-a", "."}, {}); })
                    .and_then([&](auto &&process) {
                        auto [exit_code] = stdexec::sync_wait(process->async_wait_exit()).value();
                        REQUIRE(exit_code.has_value());
                        REQUIRE(exit_code.value() == EXIT_SUCCESS);
                        return exit_code;
                    })
                    .has_value());
    }

    SECTION("A non probe process can be launched")
    {
        auto process = manager.launch_application("runnable", kRunnablePath, {}, {}).value();
        auto [exit_code] = stdexec::sync_wait(process->async_wait_exit()).value();
        REQUIRE(exit_code.has_value());
        REQUIRE(exit_code.value() == EXIT_SUCCESS);

        REQUIRE(manager.application("runnable").has_value());
        REQUIRE(manager.application("runnable").value()->exit_code() == EXIT_SUCCESS);
    }

    SECTION("A non probe process can be launched with args")
    {
        auto process = manager.launch_application("runnable", kRunnablePath, {"--exit-code", "10"}, {}).value();
        auto [exit_code] = stdexec::sync_wait(process->async_wait_exit()).value();
        REQUIRE(exit_code.has_value());
        REQUIRE(exit_code.value() == 10);
    }

    SECTION("A non probe process can be launched with a custom environment")
    {
        auto process = manager.launch_application("runnable", kRunnablePath, {}, {{"TEST_EXIT_CODE", "20"}}).value();
        auto [exit_code] = stdexec::sync_wait(process->async_wait_exit()).value();
        REQUIRE(exit_code.has_value());
        REQUIRE(exit_code.value() == 20);
    }

    SECTION("A non probe process can be launched multiple times")
    {
        for (int i = 0; i < 2; i++)
        {
            const auto expected_exit_code = i + 42;
            auto process =
                manager
                    .launch_application(
                        "runnable", kRunnablePath, {"--exit-code", fmt::format("{}", expected_exit_code)}, {})
                    .value();
            auto [exit_code] = stdexec::sync_wait(process->async_wait_exit()).value();
            REQUIRE(exit_code.has_value());
            REQUIRE(exit_code.value() == expected_exit_code);

            REQUIRE(manager.application("runnable").has_value());
            REQUIRE(manager.application("runnable").value()->exit_code() == expected_exit_code);
        }
    }

    SECTION("An invalid process will not crash")
    {
        auto process =
            manager.launch_application("not-found", "quite-not-found-program-42", {}, {{"TEST_EXIT_CODE", "42"}});
        REQUIRE_FALSE(process.has_value());
    }
}
