#include <catch2/catch_test_macros.hpp>
#include <quite/logger.hpp>
#include <quite/manager/process_manager.hpp>
#include <quite/probe.hpp>
#include <quite/probe_manager.hpp>
#include <quite/quite.hpp>
#include <quite/setup_logger.hpp>
#include "async_test_helper.hpp"
#include "tester_app.hpp"

using namespace quite;
using namespace quite::client;
using namespace quite::manager;

DEFINE_LOGGER(test);

TEST_CASE("A host application is started")
{
    setup_logger();
    ProcessManager process_manager{quite::asio_context()};
    ProbeManager probe_manager;
    auto probe = probe_manager.connect(*process_manager.launch_application({"tester"}, TESTER_APP_PATH), "...");

    ASYNC_BLOCK
    const auto state = co_await probe->wait_for_started(std::chrono::seconds{5});
    REQUIRE(state.has_value());
    co_await probe->exit();
    ASYNC_BLOCK_END
}
