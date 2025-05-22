#include <catch2/catch_test_macros.hpp>
#include <quite/asio_context.hpp>
#include <quite/logger.hpp>
#include <quite/manager/process_manager.hpp>
#include <quite/probe.hpp>
#include <quite/probe_manager.hpp>
#include <quite/property.hpp>
#include <quite/quite.hpp>
#include <quite/setup_logger.hpp>
#include <quite/utils/dump_properties.hpp>
#include <tester_app.hpp>
#include "async_test_helper.hpp"

DEFINE_LOGGER(test);

TEST_CASE("Test the qt build in meta types")
{
    // https://doc.qt.io/qt-6/qmetatype.html#Type-enum
    constexpr quite::meta::TypeId kVoidId = 43;
    quite::setup_logger();

    ASYNC_BLOCK
    quite::manager::ProcessManager process_manager{quite::get_executor()};
    quite::client::ProbeManager probe_manager;
    auto [process] = stdexec::sync_wait(process_manager.launch_application({"tester"}, TESTER_APP_PATH)).value();
    auto app = probe_manager.connect(*process, "");

    const auto void_type = co_await app->meta_registry().lookup_type(kVoidId);
    if (not void_type.has_value())
    {
        LOG_ERROR(test(), "Could not aquire type. Failed with {}", void_type.error().message);
    }

    REQUIRE(void_type.has_value());
    REQUIRE(std::holds_alternative<quite::meta::PrimitiveType>(*void_type));
    REQUIRE(std::get<quite::meta::PrimitiveType>(*void_type) == quite::meta::PrimitiveType::type_void);
    ASYNC_BLOCK_END
}
