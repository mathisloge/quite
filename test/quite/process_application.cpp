#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/steady_timer.hpp>
#include <catch2/catch_test_macros.hpp>
#include <quite/application.hpp>
#include <quite/quite.hpp>
#include <spdlog/spdlog.h>
#include <tester_app.hpp>

TEST_CASE("Test if a process application can be created")
{
    spdlog::set_level(spdlog::level::level_enum::trace);

    auto app = quite::Application::CreateApplication(TESTER_APP_PATH);

    asio::co_spawn(
        quite::globalExecutor(),
        [&]() -> asio::awaitable<void> {
            auto ex = co_await asio::this_coro::executor;

            asio::steady_timer t(ex, std::chrono::seconds(2));
            co_await t.async_wait(asio::use_awaitable);

            co_await app->test();
            co_return;
        },
        asio::detached);
    std::this_thread::sleep_for(std::chrono::seconds{1000});

    // co_await app->test();
}
