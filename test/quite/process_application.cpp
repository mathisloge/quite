#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/steady_timer.hpp>
#include <catch2/catch_test_macros.hpp>
#include <quite/application.hpp>
#include <quite/asio2exec.hpp>
#include <quite/property.hpp>
#include <quite/quite.hpp>
#include <spdlog/spdlog.h>
#include <tester_app.hpp>
#include "quite/utils/dump_properties.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

TEST_CASE("Test if a process application can be created")
{
    stdexec::sync_wait([]() -> exec::task<void> {
        spdlog::set_level(spdlog::level::level_enum::trace);

        auto app = quite::Application::CreateApplication(TESTER_APP_PATH);

        {
            auto xxxx = co_await app->find_object("testRoot");
            REQUIRE(xxxx.has_value());

            {
                auto json_props = co_await quite::dump_properties(
                    xxxx.value(), {"objectName", "width", "height", "children", "visible"});
                REQUIRE(json_props.has_value());
                std::ofstream o("pretty.json");
                o << std::setw(4) << *json_props << std::endl;
            }

            auto all_props = co_await xxxx.value()->fetch_properties({});
            REQUIRE(all_props.has_value());
            REQUIRE(all_props.value().size() > 0);
            for (auto &&p : all_props.value())
            {
                if (p.second->value().has_value())
                {
                    spdlog::info("P {}={}", p.first, p.second->value().value());
                }
                else
                {

                    spdlog::info("P {}=no value", p.first);
                }
            }

            auto snapshot = co_await xxxx.value()->take_snapshot();
            REQUIRE(snapshot.has_value());
        }
        co_await app->get_views();

        auto btn_obj = co_await app->find_object("worldBtn");
        REQUIRE(btn_obj.has_value());
        auto text_area_res = co_await app->find_object("textArea");
        REQUIRE(text_area_res.has_value());
        auto text_area = text_area_res.value();
        {
            const auto text_prop = co_await text_area->property("text");
            REQUIRE(text_prop.has_value());
            REQUIRE(std::get<std::string>((co_await text_prop.value()->read()).value_or("xxx")) == "...");
        }
        co_await btn_obj.value()->mouse_action();
        {
            auto text_prop = co_await text_area->fetch_properties({"text"});
            REQUIRE(text_prop.has_value());
            REQUIRE(std::get<std::string>(text_prop.value().at("text")->value().value()) == "World");
        }
        auto img = co_await btn_obj.value()->take_snapshot();
        REQUIRE(img.has_value());
        img->save_to("/home/mathis/dev/ng-quite/test2.png");
        co_return;
    }());
}
