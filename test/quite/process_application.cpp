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

        

        auto btn_obj = co_await app->find_object("helloBtn");
        REQUIRE(btn_obj.has_value());
        auto text_area_res = co_await app->find_object("textArea");
        REQUIRE(text_area_res.has_value());
        auto text_area = text_area_res.value();
        {
            auto text_prop = co_await text_area->get_property("text");
            REQUIRE(text_prop.has_value());
            REQUIRE(text_prop->value == "...");
        }
        co_await btn_obj.value()->mouse_action();
        {
            auto text_prop = co_await text_area->get_property("text");
            REQUIRE(text_prop.has_value());
            REQUIRE(text_prop->value == "Hello");
        }
        //co_await text_area.value()->take_snapshot();
        co_return;
    }());
}
