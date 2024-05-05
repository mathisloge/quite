#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/steady_timer.hpp>
#include <catch2/catch_test_macros.hpp>
#include <quite/application.hpp>
#include <quite/asio2exec.hpp>
#include <quite/quite.hpp>
#include <spdlog/spdlog.h>
#include <tester_app.hpp>

TEST_CASE("Test if a process application can be created")
{
    spdlog::set_level(spdlog::level::level_enum::trace);

    auto app = quite::Application::CreateApplication(TESTER_APP_PATH);

    auto [remote_obj] = stdexec::sync_wait(app->find_object("testRoot2")).value();
    REQUIRE(remote_obj.has_value());

    auto [property] = stdexec::sync_wait(remote_obj.value()->get_property("objectName")).value();
    REQUIRE(property.value == "testRoot2");
}
