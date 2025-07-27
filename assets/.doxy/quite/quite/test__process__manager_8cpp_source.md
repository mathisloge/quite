

# File test\_process\_manager.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**manager**](dir_b048ed2415d89a3588bcd07e27f16f41.md) **>** [**tests**](dir_0da81ac3ea6d1987f7ba9a902aa51f1c.md) **>** [**test\_process\_manager.cpp**](test__process__manager_8cpp.md)

[Go to the documentation of this file](test__process__manager_8cpp.md)


```C++
#include <catch2/catch_test_macros.hpp>
#include <quite/asio_context.hpp>
#include <quite/manager/process.hpp>
#include <quite/manager/process_manager.hpp>
#include <quite/setup_logger.hpp>
#include "runnable_path.hpp"

using namespace quite::manager;

TEST_CASE("Test ProcessManager", "[manager]")
{
    quite::setup_logger();
    ProcessManager manager{quite::get_executor()};

    SECTION("A non probe process from environment can be launched")
    {
        auto [exe] = stdexec::sync_wait(manager.find_executable({"ls"})).value();
        REQUIRE(exe.and_then([&](auto &&path) {
                       return std::get<0>(
                           stdexec::sync_wait(manager.launch_application({"ls"}, path, {"-a", "."}, {})).value());
                   })
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
        auto [process] = stdexec::sync_wait(manager.launch_application({"runnable"}, kRunnablePath, {}, {})).value();
        auto [exit_code] = stdexec::sync_wait(process.value()->async_wait_exit()).value();
        REQUIRE(exit_code.has_value());
        REQUIRE(exit_code.value() == EXIT_SUCCESS);

        auto [runnable] = stdexec::sync_wait(manager.application({"runnable"})).value();
        REQUIRE(runnable.has_value());
        REQUIRE(runnable.value()->exit_code() == EXIT_SUCCESS);
    }

    SECTION("A non probe process can be launched with args")
    {
        auto [process] =
            stdexec::sync_wait(manager.launch_application({"runnable"}, kRunnablePath, {"--exit-code", "10"}, {}))
                .value();
        auto [exit_code] = stdexec::sync_wait(process.value()->async_wait_exit()).value();
        REQUIRE(exit_code.has_value());
        REQUIRE(exit_code.value() == 10);
    }

    SECTION("A non probe process can be launched with a custom environment")
    {
        auto [process] =
            stdexec::sync_wait(manager.launch_application({"runnable"}, kRunnablePath, {}, {{"TEST_EXIT_CODE", "20"}}))
                .value();
        auto [exit_code] = stdexec::sync_wait(process.value()->async_wait_exit()).value();
        REQUIRE(exit_code.has_value());
        REQUIRE(exit_code.value() == 20);
    }

    SECTION("A non probe process can be launched multiple times")
    {
        for (int i = 0; i < 2; i++)
        {
            const auto expected_exit_code = i + 42;
            auto [process] =
                stdexec::sync_wait(
                    manager.launch_application(
                        {"runnable"}, kRunnablePath, {"--exit-code", fmt::format("{}", expected_exit_code)}, {}))
                    .value();
            auto [exit_code] = stdexec::sync_wait(process.value()->async_wait_exit()).value();
            REQUIRE(exit_code.has_value());
            REQUIRE(exit_code.value() == expected_exit_code);

            auto [runnable] = stdexec::sync_wait(manager.application({"runnable"})).value();
            REQUIRE(runnable.has_value());
            REQUIRE(runnable.value()->exit_code() == expected_exit_code);
        }
    }

    SECTION("An invalid process will not crash")
    {
        auto [process] =
            stdexec::sync_wait(
                manager.launch_application({"not-found"}, "quite-not-found-program-42", {}, {{"TEST_EXIT_CODE", "42"}}))
                .value();
        REQUIRE_FALSE(process.has_value());
    }
}
```


