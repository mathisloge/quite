#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/steady_timer.hpp>
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>
#include <quite/application.hpp>
#include <quite/asio2exec.hpp>
#include <quite/logger.hpp>
#include <quite/property.hpp>
#include <quite/quite.hpp>
#include <quite/setup_logger.hpp>
#include <quite/utils/dump_properties.hpp>
#include <tester_app.hpp>
#include "async_test_helper.hpp"

DEFINE_LOGGER(test);

TEST_CASE("Test if a process application can be created")
{
    quite::setup_logger();

    ASYNC_BLOCK
    auto app = quite::Application::CreateApplication(TESTER_APP_PATH);

    const auto myCustomType = co_await app->meta_type_registry().resolve_type("MyCustomType");
    /*
    if (not myCustomType.has_value())
    {
        LOG_ERROR(test, "Could not aquire type. Failed with {}", myCustomType.error().message);
    }
    REQUIRE(myCustomType.has_value());
    */
    ASYNC_BLOCK_END
}
