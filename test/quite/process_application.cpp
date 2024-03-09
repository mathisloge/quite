#include <catch2/catch_test_macros.hpp>
#include <quite/application.hpp>
#include <spdlog/spdlog.h>
#include <tester_app.hpp>

TEST_CASE("Test if a process application can be created")
{
    spdlog::set_level(spdlog::level::level_enum::trace);

    auto app = quite::Application::CreateApplication(TESTER_APP_PATH);

    //co_await app->test();
}
