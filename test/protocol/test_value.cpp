#include <catch2/catch_test_macros.hpp>
#include <entt/core/hashed_string.hpp>
#include <entt/meta/container.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <quite/proto/value.hpp>
#include <quite/value/generic_value_class.hpp>
#include <quite/value/value_registry.hpp>

using namespace entt::literals;

struct TestData
{
    bool val_bool{};
    int val_int{};
    std::uint32_t val_uint{};
    double val_double{};
    std::string val_str;
};

TEST_CASE("Test value")
{
    quite::ValueRegistry value_registry;
    entt::meta_factory<TestData>() //
        .data<&TestData::val_bool>(value_registry.named_property("val_bool"))
        .data<&TestData::val_int>(value_registry.named_property("val_int"))
        .data<&TestData::val_uint>(value_registry.named_property("val_uint"))
        .data<&TestData::val_double>(value_registry.named_property("val_double"))
        .data<&TestData::val_str>(value_registry.named_property("val_str"));

    entt::meta_factory<quite::GenericClass>()
        .type("GenericClass"_hs)
        .data<&quite::GenericClass::properties>("properties"_hs);

    const TestData test_data{
        .val_bool = true, .val_int = -10, .val_uint = 20, .val_double = 200.1345, .val_str = "hello world"};
    SECTION("struct")
    {
        const entt::meta_any meta_data = entt::forward_as_meta(test_data);
        auto value = quite::proto::create_value(value_registry, meta_data);
        REQUIRE(value.has_class_val());
        auto &&class_val = value.class_val();
        REQUIRE(class_val.value().size() == 5);
        REQUIRE(class_val.value()[0].name() == "val_bool");
        REQUIRE(class_val.value()[1].name() == "val_int");
        REQUIRE(class_val.value()[2].name() == "val_uint");
        REQUIRE(class_val.value()[3].name() == "val_double");
        REQUIRE(class_val.value()[4].name() == "val_str");
        REQUIRE(class_val.value()[0].value().has_bool_val());
        REQUIRE(class_val.value()[1].value().has_int_val());
        REQUIRE(class_val.value()[2].value().has_uint_val());
        REQUIRE(class_val.value()[3].value().has_double_val());
        REQUIRE(class_val.value()[4].value().has_string_val());
    }

    SECTION("generic class")
    {
        quite::GenericClass generic{};
        generic.properties.emplace("test", test_data);
        REQUIRE(generic.properties.size() == 1);

        const entt::meta_any generic_meta = entt::forward_as_meta(generic);
        entt::meta_associative_container meta_properties = generic_meta.get("properties"_hs).as_associative_container();
        REQUIRE(meta_properties.size() == 1);

        auto value = quite::proto::create_value(value_registry, generic_meta);
        REQUIRE(value.has_class_val());
        auto &&class_val = value.class_val();
        REQUIRE(class_val.value().size() == 1);
        REQUIRE(class_val.value()[0].name() == "test");
        REQUIRE(class_val.value()[0].has_value());
        REQUIRE(class_val.value()[0].value().has_class_val());
        REQUIRE(class_val.value()[0].value().class_val().value().size() == 5);
    }
}
