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

        auto btn_obj = co_await app->find_object("worldBtn");
        REQUIRE(btn_obj.has_value());
        auto text_area_res = co_await app->find_object("textArea");
        REQUIRE(text_area_res.has_value());
        auto text_area = text_area_res.value();
        {
            auto text_prop = co_await text_area->fetch_properties({"text"});
            REQUIRE(text_prop.has_value());
            REQUIRE(text_prop.value()[0].value.value == "...");
        }
        co_await btn_obj.value()->mouse_action();
        {
            auto text_prop = co_await text_area->fetch_properties({"text"});
            REQUIRE(text_prop.has_value());
            REQUIRE(text_prop.value()[0].value.value == "World");
        }
        auto img = co_await btn_obj.value()->take_snapshot();
        REQUIRE(img.has_value());
        img->save_to("/home/mathis/dev/ng-quite/test2.png");
        co_return;
    }());
}
