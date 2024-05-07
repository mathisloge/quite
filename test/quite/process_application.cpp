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
    stdexec::sync_wait([]() -> exec::task<void> {
        spdlog::set_level(spdlog::level::level_enum::trace);

        auto app = quite::Application::CreateApplication(TESTER_APP_PATH);

        auto remote_obj = co_await app->find_object("helloBtn");
        REQUIRE(remote_obj.has_value());

        auto property = co_await remote_obj.value()->get_property("objectName");
        REQUIRE(property.value == "helloBtn");

        co_await remote_obj.value()->mouse_click();
        std::this_thread::sleep_for(std::chrono::seconds{1});
        auto text_area = co_await app->find_object("textArea");
        auto text_prop = co_await text_area.value()->get_property("text");
        REQUIRE(text_prop.value == "Hello");
        co_return;
    }());
}
