#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>
#include <quite/application.hpp>
#include <quite/application_manager.hpp>
#include <quite/asio2exec.hpp>
#include <quite/logger.hpp>
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
    quite::ApplicationManager app_manager;
    auto app = app_manager.create_host_application(TESTER_APP_PATH);

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
