#include <QObject>
#include <atomic>
#include <catch2/catch_test_macros.hpp>
#include <entt/meta/factory.hpp>
#include <fmt/base.h>
#include <qmetaobject.h>
#include <quite/proto/types.pb.h>

using namespace entt::literals;

namespace
{
struct SimpleStruct
{
    int a;
    std::string b;
};

quite::proto::Value to_value(const SimpleStruct &data)
{
    quite::proto::Value value;

    auto &&class_val = value.mutable_class_val();

    class_val->set_type_name("SimpleStruct");
    {
        auto &&member = class_val->add_value();
        member->set_name("a");
        member->mutable_value()->set_int_val(data.a);
    }
    {
        auto &&member = class_val->add_value();
        member->set_name("b");
        member->mutable_value()->set_string_val(data.b);
    }

    return value;
}

} // namespace

TEST_CASE("Register struct and convert it to a protocol value", "[meta,design-test]")
{
    entt::meta<SimpleStruct>()
        .type("SimpleStruct"_hs)
        .data<&SimpleStruct::a>("a"_hs)
        .data<&SimpleStruct::b>("b"_hs)
        .conv<to_value>();

    auto simple_struct = entt::resolve<SimpleStruct>().construct();
    REQUIRE(simple_struct.set("a"_hs, 100));
    REQUIRE(simple_struct.set("b"_hs, std::string{"test"}));
    const SimpleStruct simple_struct_fin = simple_struct.cast<SimpleStruct>();

    REQUIRE(simple_struct.allow_cast<quite::proto::Value>());
    quite::proto::Value value = simple_struct.cast<quite::proto::Value>();
    REQUIRE(value.has_class_val());
    REQUIRE(value.class_val().value(0).has_value());
    REQUIRE(value.class_val().value(0).name() == "a");
    REQUIRE(value.class_val().value(0).has_value());
    REQUIRE(value.class_val().value(0).value().has_int_val());
    REQUIRE(value.class_val().value(0).value().int_val() == 100);

    REQUIRE(value.class_val().value(1).has_value());
    REQUIRE(value.class_val().value(1).name() == "b");
    REQUIRE(value.class_val().value(1).has_value());
    REQUIRE(value.class_val().value(1).value().has_string_val());
    REQUIRE(value.class_val().value(1).value().string_val() == "test");

    auto simple_struct_type = entt::resolve(entt::hashed_string{value.class_val().type_name().c_str()}.value());
    REQUIRE(simple_struct_type);

    auto back_cnv_struct = simple_struct_type.construct();

    for (auto &&val : value.class_val().value())
    {
        const auto id = entt::hashed_string{val.name().c_str()}.value();
        if (val.value().has_int_val())
        {
            back_cnv_struct.set(id, val.value().int_val());
        }
        else if (val.value().has_string_val())
        {
            back_cnv_struct.set(id, val.value().string_val());
        }
    }

    const SimpleStruct struct_val = back_cnv_struct.cast<SimpleStruct>();
    REQUIRE(simple_struct_fin.a == struct_val.a);
    REQUIRE(simple_struct_fin.b == struct_val.b);
}

class MyOwnClass : public QObject
{
    Q_OBJECT
};

TEST_CASE("API DESIGN META RUNTIME")
{
    constexpr auto kMetaType = QMetaType::fromType<MyOwnClass>();

    kMetaType.metaObject()->method(0).parameterType(0);
}

#include "test_object_registry.moc"
