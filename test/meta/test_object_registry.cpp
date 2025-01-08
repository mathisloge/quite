#include <QObject>
#include <catch2/catch_test_macros.hpp>
#include <entt/meta/factory.hpp>
#include <fmt/base.h>
#include <qmetaobject.h>
#include <quite/proto/methods.pb.h>
#include <quite/proto/types.pb.h>
#include <value_converters.hpp>

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
    entt::meta_factory<SimpleStruct>()
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

  public Q_SLOTS:
    quint64 compute(quint64 val1, quint8 val2)
    {
        return val1 + val2;
    }

    quint64 compute(float val1, qint8 val2)
    {
        return 200 * 10;
    }
};

TEST_CASE("API DESIGN META RUNTIME")
{
    constexpr auto kMetaType = QMetaType::fromType<MyOwnClass>();

    kMetaType.metaObject()->method(0).parameterType(0);
}

TEST_CASE("Test meta method call")
{
    quite::probe::register_converters();

    MyOwnClass test_obj{};

    QByteArray normalized_signature = QMetaObject::normalizedSignature("compute(float, qint8)");
    const auto *meta_object = test_obj.metaObject();
    int method_index = meta_object->indexOfMethod(normalized_signature);

    for (int i = 0; i < meta_object->methodCount(); i++)
    {
        qDebug() << meta_object->method(i).name();
    }

    QMetaMethod method = test_obj.metaObject()->method(method_index);
    REQUIRE(method.isValid());

    auto &&param1 = method.parameterMetaType(0);

    double initial_val{5};
    REQUIRE(QMetaType::canConvert(QMetaType::fromType<double>(), QMetaType::fromType<float>()));
    auto *val1 = param1.create();
    QMetaType::convert(QMetaType::fromType<double>(), &initial_val, param1, val1);
    QMetaMethodArgument arg3{.metaType = param1.iface(), .name = param1.name(), .data = val1};

    qDebug() << arg3.metaType << arg3.name << arg3.data;

    quint64 result{};
    auto infoke_result = method.invoke(&test_obj, Qt::DirectConnection, qReturnArg(result), arg3, qint8{5});

    REQUIRE(infoke_result);
    REQUIRE(result == 2000);
}

namespace
{
template <std::size_t... S>
bool invoke_method(QMetaMethod &method,
                   QObject *obj,
                   QMetaMethodReturnArgument &result,
                   const std::vector<QMetaMethodArgument> &args,
                   std::index_sequence<S...>)
{
    return method.invoke(obj, Qt::DirectConnection, result, args[S]...);
}

template <std::size_t TSize>
bool invoke_method(QMetaMethod &method,
                   QObject *obj,
                   QMetaMethodReturnArgument &result,
                   const std::vector<QMetaMethodArgument> &args)
{
    Q_ASSERT(TSize == args.size());
    return invoke_method(method, obj, result, args, std::make_index_sequence<TSize>());
}

QMetaType from_value(const quite::proto::Value &value)
{
    if (value.has_double_val())
    {
        return QMetaType::fromType<double>();
    }
    if (value.has_uint_val())
    {
        return QMetaType::fromType<std::uint64_t>();
    }
    if (value.has_string_val())
    {
        return QMetaType::fromType<QString>();
    }
    if (value.has_object_val())
    {
        return reinterpret_cast<QObject *>(value.object_val().object_id())->metaObject()->metaType();
    }
    return QMetaType{};
}
} // namespace

TEST_CASE("EXP. API meta call")
{
    quite::proto::MethodCall method_call_proto{};

    method_call_proto.set_method_name("compute(float, qint8)");
    auto &&arg1 = method_call_proto.add_argument();
    auto &&arg2 = method_call_proto.add_argument();
    arg1->set_double_val(10);
    arg2->set_uint_val(5);

    MyOwnClass test_obj{};

    const auto *meta_object = test_obj.metaObject();
    const QByteArray normalized_method_signature =
        QMetaObject::normalizedSignature(method_call_proto.method_name().c_str());
    const int method_index = meta_object->indexOfMethod(normalized_method_signature);
    QMetaMethod method = test_obj.metaObject()->method(method_index);
    REQUIRE(method.isValid());
    REQUIRE(method.parameterCount() == method_call_proto.argument_size());

    std::vector<void *> args;
    const auto method_return_type = method.returnMetaType();
    auto *return_val = method_return_type.create();
    args.emplace_back(return_val);

    // std::vector<QMetaMethodArgument> args;
    for (int i = 0; i < method.parameterCount(); i++)
    {
        auto &&method_param = method.parameterMetaType(i);
        auto *param_val = method_param.create();
        auto &&proto_val = method_call_proto.argument(i);

        REQUIRE(QMetaType::canConvert(from_value(proto_val), method_param));
        // convert_to_value(protoval, method_param, param_val);

        args.emplace_back(param_val); // todo: destroy
    }
    const auto invoke_res = test_obj.qt_metacall(QMetaObject::Call::InvokeMetaMethod, method_index, args.data());
    const bool invoked = invoke_res < 0;
    REQUIRE(invoked);
    REQUIRE(*static_cast<quint64 *>(return_val) == 2000);
}

#include "test_object_registry.moc"
