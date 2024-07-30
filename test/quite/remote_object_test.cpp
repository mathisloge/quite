#include <catch2/catch_test_macros.hpp>
#include <exec/task.hpp>
#include <quite/application.hpp>
#include <spdlog/spdlog.h>
#include "tester_app.hpp"

#define ASYNC_BLOCK stdexec::sync_wait([&]() -> exec::task<void> {

#define ASYNC_BLOCK_END                                                                                                \
    co_return;                                                                                                         \
    }());

using namespace quite;

TEST_CASE("Remote object can be invoked")
{
    spdlog::set_level(spdlog::level::level_enum::trace);
    auto app = Application::CreateApplication(TESTER_APP_PATH);

    const ObjectQuery btn_query{.properties = {{"objectName", Value{"helloBtn"}}}};
    auto obj = std::get<RemoteObjectPtr>(stdexec::sync_wait([&]() -> exec::task<RemoteObjectPtr> {
                                             auto obj = co_await app->find_object(btn_query);
                                             REQUIRE(obj.has_value());
                                             co_return obj.value();
                                         }())
                                             .value());

    SECTION("The property text should have the value of the button")
    {
        ASYNC_BLOCK
        auto prop = co_await obj->property("text");
        REQUIRE(prop.has_value());

        auto &&val = prop.value()->value();
        REQUIRE(val.has_value());
        REQUIRE(std::holds_alternative<std::string>(val.value()));
        REQUIRE(std::get<std::string>(*val) == "Hello");

        ASYNC_BLOCK_END
    }

    SECTION("Click the Button, then the text should have changed")
    {
        const ObjectQuery query{.properties = {{"objectName", "textArea"}}};

        ASYNC_BLOCK
        auto text_area = co_await app->find_object(query);
        REQUIRE(std::get<std::string>(*(co_await text_area.value()->property("text")).value()->value()) == "...");
        co_await obj->mouse_action();
        REQUIRE(std::get<std::string>(*(co_await text_area.value()->property("text")).value()->value()) == "Hello");

        ASYNC_BLOCK_END
    }

    SECTION("A snapshot can be taken of the object")
    {
        ASYNC_BLOCK

        auto img = co_await obj->take_snapshot();
        REQUIRE(img.has_value());
        REQUIRE(img->data().data.size() == (100 * 30 * 4));
        REQUIRE(img->data().channels == 4);
        REQUIRE(img->data().width == 100);
        REQUIRE(img->data().height == 30);

        ASYNC_BLOCK_END
    }

    SECTION("App can be quit")
    {
        ASYNC_BLOCK
        co_await app->exit();
        ASYNC_BLOCK_END
    }
}
