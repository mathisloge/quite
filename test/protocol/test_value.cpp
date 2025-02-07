#include <catch2/catch_test_macros.hpp>
#include <entt/core/hashed_string.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <quite/proto/traits.hpp>
#include <quite/proto/value.hpp>

using namespace entt::literals;

struct TestData
{
    int x;
    double y;
    std::string z;
};

TEST_CASE("Test value")
{
    entt::dense_map<entt::hashed_string::hash_type, std::string> property_name_db;

    property_name_db.emplace("x"_hs, "x");
    property_name_db.emplace("y"_hs, "y");
    property_name_db.emplace("z"_hs, "z");

    entt::meta_factory<TestData>().data<&TestData::x>("x"_hs).data<&TestData::y>("y"_hs).data<&TestData::z>("z"_hs);

    const entt::meta_any meta_data = TestData{.x = 10, .y = 200.1345, .z = "hello world"};

    auto value = quite::proto::create_value(property_name_db, meta_data);
    REQUIRE(value.has_class_val());
    auto &&class_val = value.class_val();
    REQUIRE(class_val.value().size() == 3);
    REQUIRE(class_val.value()[0].name() == "x");
    REQUIRE(class_val.value()[1].name() == "y");
    REQUIRE(class_val.value()[2].name() == "z");
    REQUIRE(class_val.value()[0].value().has_int_val());
    REQUIRE(class_val.value()[1].value().has_double_val());
    REQUIRE(class_val.value()[2].value().has_string_val());
}
