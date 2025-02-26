#include <QCoreApplication>
#include <QEventLoop>
#include <catch2/catch_test_macros.hpp>
#include <exec/async_scope.hpp>
#include <object_handler.hpp>
#include <quite/logger.hpp>
#include "async_test_helper.hpp"
#include "object_tracker.hpp"
#include "probe_instances.hpp"
#include "qtstdexec.h"

using namespace quite;
using namespace quite::probe;
using namespace entt::literals;

DEFINE_LOGGER(test)

namespace
{
void spin_eventloop_once()
{
    QEventLoop loop;
    REQUIRE(loop.processEvents());
}
} // namespace
TEST_CASE("Test ProbeHandler")
{
    ObjectTracker tracker;
    // ProbeInstances instances{tracker};
    ObjectHandler probe_handler{tracker};

    QObject test_obj{};
    const auto test_obj_id = reinterpret_cast<ObjectId>(std::addressof(test_obj));
    test_obj.setObjectName("Test");

    tracker.add_object(std::addressof(test_obj));
    spin_eventloop_once();

    SECTION("test object_instance")
    {
        ASYNC_BLOCK
        auto invalid_result = co_await probe_handler.object_instance(123);
        REQUIRE_FALSE(invalid_result.has_value());
        auto valid_result = co_await probe_handler.object_instance(test_obj_id);
        REQUIRE(valid_result.has_value());
        REQUIRE(valid_result.value() == std::addressof(test_obj));
        ASYNC_BLOCK_END
    }

    SECTION("test fetch_properties all")
    {
        bool do_spin{true};
        exec::async_scope scope;
        auto snd = stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())) |
                   stdexec::let_value([&]() { return probe_handler.fetch_properties(test_obj_id, {}); }) |
                   stdexec::then([](auto &&result) {
                       REQUIRE(result.has_value());
                       QCoreApplication::quit();
                   });
        scope.spawn(std::move(snd));

        QCoreApplication::exec();
    }

    SECTION("test fetch_properties filtered")
    {}
}
