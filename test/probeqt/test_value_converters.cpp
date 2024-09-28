#include <QColor>
#include <catch2/catch_test_macros.hpp>
#include <entt/locator/locator.hpp>
#include <entt/meta/factory.hpp>
#include <probe_context.hpp>
#include <value_converters.hpp>

using namespace quite;
using namespace quite::probe;

TEST_CASE("Test value converters")
{
    register_converters();
    SECTION("QColor conversions")
    {
        QColor color{Qt::blue};

        auto custom_meta_type = entt::resolve(entt::hashed_string{QMetaType::fromType<QColor>().name()}.value());
        REQUIRE(custom_meta_type);

        custom_meta_type = entt::resolve<QColor>();
        REQUIRE(custom_meta_type);

        auto &&any_obj = custom_meta_type.from_void(&color);
        REQUIRE(any_obj.allow_cast<proto::Value>());
        const auto value = any_obj.cast<proto::Value>();

        REQUIRE(value.has_class_val());
        REQUIRE(value.class_val().type_name() == "QColor");
        REQUIRE(value.class_val().value().size() == 1);
        REQUIRE(value.class_val().value()[0].name() == "argb");
        REQUIRE(value.class_val().value()[0].value().has_string_val());
        REQUIRE(value.class_val().value()[0].value().string_val() == "#ff0000ff");
    }
}