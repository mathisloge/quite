#include <catch2/catch_test_macros.hpp>
#include <quite/application.hpp>
#include <quite/application_manager.hpp>
#include <quite/logger.hpp>
#include <quite/setup_logger.hpp>
#include "async_test_helper.hpp"
#include "tester_app.hpp"

using namespace quite;

DEFINE_LOGGER(test);

TEST_CASE("A host application is started")
{
    setup_logger();
    ApplicationManager app_manager;
    auto app = app_manager.create_host_application(TESTER_APP_PATH);

    ASYNC_BLOCK
    const auto state = co_await app->wait_for_started();
    REQUIRE(state.has_value());
    co_await app->exit();
    ASYNC_BLOCK_END
}
