#include <catch2/catch_test_macros.hpp>
#include <exec/task.hpp>
#include <quite/logger.hpp>
#include <quite/manager/process_manager.hpp>
#include <quite/probe.hpp>
#include <quite/probe_manager.hpp>
#include <quite/setup_logger.hpp>
#include <quite/testing/verification_point.hpp>
#include "async_test_helper.hpp"
#include "quite/quite.hpp"
#include "tester_app.hpp"

using namespace quite;

DEFINE_LOGGER(test);

TEST_CASE("Remote object can be invoked")
{
    setup_logger();
    quite::manager::ProcessManager process_manager{quite::asio_context()};
    quite::client::ProbeManager probe_manager;
    auto app = probe_manager.connect(*process_manager.launch_application({"tester"}, TESTER_APP_PATH), "");
    stdexec::sync_wait(app->wait_for_started(std::chrono::seconds{5}));

    const ObjectQuery btn_query{.properties = {{"objectName", entt::forward_as_meta(std::string{"helloBtn"})}}};
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
        // REQUIRE(std::holds_alternative<std::string>(val.value()));
        // REQUIRE(std::get<std::string>(*val) == "Hello");

        ASYNC_BLOCK_END
    }

    SECTION("Click the Button, then the text should have changed")
    {
        const ObjectQuery query{.properties = {{"objectName", std::string{"textArea"}}}};

        ASYNC_BLOCK
        auto text_area = co_await app->find_object(query);
        REQUIRE(text_area.has_value());
        // REQUIRE(std::get<std::string>(*(co_await text_area.value()->property("text")).value()->value()) == "...");
        co_await obj->mouse_action();
        // REQUIRE(std::get<std::string>(*(co_await text_area.value()->property("text")).value()->value()) == "Hello");

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

    SECTION("A verification point is checked")
    {
        ASYNC_BLOCK

        co_await testing::create_verification_point(obj, "btn_test");

        const auto res = co_await testing::verify_verification_point(obj, "btn_test");
        REQUIRE(res.has_value());
        REQUIRE(res.value());

        ASYNC_BLOCK_END
    }

    SECTION("The meta type can be fetched")
    {
        ASYNC_BLOCK
        const auto obj_meta_type = co_await app->meta_registry().lookup_type(obj->type_id());
        REQUIRE(obj_meta_type.has_value());
        ASYNC_BLOCK_END
    }

    SECTION("A method is invoked")
    {
        ASYNC_BLOCK
        auto invoke_result = co_await obj->invoke_method("click()");
        REQUIRE(invoke_result.has_value());
        const ObjectQuery text_area_query{.properties = {{"objectName", std::string{"textArea"}}}};
        auto text_area = std::get<RemoteObjectPtr>(stdexec::sync_wait([&]() -> exec::task<RemoteObjectPtr> {
                                                       auto obj = co_await app->find_object(text_area_query);
                                                       REQUIRE(obj.has_value());
                                                       co_return obj.value();
                                                   }())
                                                       .value());

        auto text_prop = co_await text_area->property("text");
        REQUIRE(text_prop.has_value());
        // REQUIRE(std::get<std::string>(*text_prop.value()->value()) == "Hello");

        ASYNC_BLOCK_END

        LOG_DEBUG(test(), "finished");
    }

    SECTION("App can be quit")
    {
        ASYNC_BLOCK
        co_await app->exit();
        ASYNC_BLOCK_END
    }
}
