#include "value_converters.hpp"
#include <QColor>
#include <QMetaType>
#include <QObject>
#include <QQmlListProperty>
#include <QQmlListReference>
#include <QQuickItem>
#include <quite/proto/types.pb.h>

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
namespace quite::probe
{
namespace
{
constexpr auto value_meta = QMetaType::fromType<proto::Value>();
}

template <typename TBase, auto TFncPtr>
void register_trivial_converter()
{
    QMetaType::registerConverter<TBase, proto::Value>([](const TBase &value) {
        proto::Value cnv;
        std::invoke(TFncPtr, cnv, value);
        return cnv;
    });
}

#define ADD_CLASS_MEMBER(member_name)                                                                                  \
    {                                                                                                                  \
        auto &&member_val = object_val->add_value();                                                                   \
        *member_val->mutable_name() = #member_name;                                                                    \
        auto &&read_member = value.member_name();                                                                      \
        QMetaType::convert(QMetaType::fromType<std::remove_cvref_t<decltype(read_member)>>(),                          \
                           &read_member,                                                                               \
                           value_meta,                                                                                 \
                           member_val->mutable_value());                                                               \
    }

#define ADD_CLASS_CONVERTER(class_name)                                                                                \
    QMetaType::registerConverter<class_name, proto::Value>([](const class_name &value) {                               \
    proto::Value cnv;                                                                                                  \
    auto &&object_val = cnv.mutable_class_val();                                                                       \
    *object_val->mutable_type_name() = #class_name;

#define END_CLASS_CONVERTER                                                                                            \
    return cnv;                                                                                                        \
    });

using namespace entt::literals;

namespace
{
auto set_trivial_member(quite::proto::ClassValue_ClassMember &member, float data)
{
    auto &&val = member.mutable_value();
    val->set_double_val(data);
}
auto set_trivial_member(quite::proto::ClassValue_ClassMember &member, double data)
{
    auto &&val = member.mutable_value();
    val->set_double_val(data);
}
auto set_trivial_member(quite::proto::ClassValue_ClassMember &member, bool data)
{
    auto &&val = member.mutable_value();
    val->set_bool_val(data);
}
auto set_trivial_member(quite::proto::ClassValue_ClassMember &member, qint8 data)
{
    auto &&val = member.mutable_value();
    val->set_int_val(data);
}
auto set_trivial_member(quite::proto::ClassValue_ClassMember &member, qint16 data)
{
    auto &&val = member.mutable_value();
    val->set_int_val(data);
}
auto set_trivial_member(quite::proto::ClassValue_ClassMember &member, qint32 data)
{
    auto &&val = member.mutable_value();
    val->set_int_val(data);
}
auto set_trivial_member(quite::proto::ClassValue_ClassMember &member, qint64 data)
{
    auto &&val = member.mutable_value();
    val->set_int_val(data);
}
auto set_trivial_member(quite::proto::ClassValue_ClassMember &member, quint8 data)
{
    auto &&val = member.mutable_value();
    val->set_uint_val(data);
}
auto set_trivial_member(quite::proto::ClassValue_ClassMember &member, quint16 data)
{
    auto &&val = member.mutable_value();
    val->set_uint_val(data);
}
auto set_trivial_member(quite::proto::ClassValue_ClassMember &member, quint32 data)
{
    auto &&val = member.mutable_value();
    val->set_uint_val(data);
}

proto::Value convert_qrectf(const QRectF &data)
{
    constexpr auto kType = QMetaType::fromType<QRectF>();
    proto::Value value;
    auto &&class_val = value.mutable_class_val();
    class_val->set_type_name(kType.name());
    {
        auto &&member = class_val->add_value();
        member->set_name("x");
        set_trivial_member(*member, data.x());
    }
    {
        auto &&member = class_val->add_value();
        member->set_name("y");
        member->mutable_value()->set_double_val(data.y());
    }
    {
        auto &&member = class_val->add_value();
        member->set_name("width");
        member->mutable_value()->set_double_val(data.width());
    }
    {
        auto &&member = class_val->add_value();
        member->set_name("height");
        member->mutable_value()->set_double_val(data.height());
    }
    return value;
}
proto::Value convert_qpointf(const QPointF &data)
{
    constexpr auto kType = QMetaType::fromType<QPointF>();
    proto::Value value;
    auto &&class_val = value.mutable_class_val();
    class_val->set_type_name(kType.name());
    {
        auto &&member = class_val->add_value();
        member->set_name("x");
        member->mutable_value()->set_double_val(data.x());
    }
    {
        auto &&member = class_val->add_value();
        member->set_name("y");
        member->mutable_value()->set_double_val(data.y());
    }
    return value;
}

proto::Value convert_qurl(const QUrl &data)
{
    constexpr auto kType = QMetaType::fromType<QUrl>();
    proto::Value value;
    auto &&class_val = value.mutable_class_val();
    class_val->set_type_name(kType.name());
    {
        auto &&member = class_val->add_value();
        member->set_name("url");
        member->mutable_value()->set_string_val(data.toDisplayString().toStdString());
    }
    return value;
}

} // namespace

void register_converters()
{
    register_trivial_converter<float, &proto::Value::set_double_val>();
    register_trivial_converter<double, &proto::Value::set_double_val>();
    register_trivial_converter<bool, &proto::Value::set_bool_val>();
    register_trivial_converter<qint8, &proto::Value::set_int_val>();
    register_trivial_converter<qint16, &proto::Value::set_int_val>();
    register_trivial_converter<qint32, &proto::Value::set_int_val>();
    register_trivial_converter<qint64, &proto::Value::set_int_val>();
    register_trivial_converter<quint8, &proto::Value::set_int_val>();
    register_trivial_converter<quint16, &proto::Value::set_int_val>();
    register_trivial_converter<quint32, &proto::Value::set_int_val>();

    QMetaType::registerConverter<QString, proto::Value>([](const QString &value) {
        proto::Value cnv;
        *cnv.mutable_string_val() = value.toStdString();
        return cnv;
    });

    QMetaType::registerConverter<QObjectList, proto::Value>([](const QObjectList &values) {
        proto::Value cnv;
        for (auto &&value : std::as_const(values))
        {
            cnv.mutable_array_val()->add_value()->mutable_object_val()->set_object_id(
                reinterpret_cast<std::uint64_t>(value));
        }
        return cnv;
    });

    entt::meta<QString>().type("QString"_hs).conv<&QString::toStdString>();

    entt::meta<QRect>()
        .type("QRect"_hs)
        .ctor<qreal, qreal, qreal, qreal>()
        .data<&QRectF::setX, &QRectF::x>("x"_hs)
        .data<&QRectF::setY, &QRectF::y>("y"_hs)
        .data<&QRectF::setWidth, &QRectF::width>("width"_hs)
        .data<&QRectF::setHeight, &QRectF::height>("height"_hs)
        .conv<convert_qrectf>();

    entt::meta<QRectF>()
        .type("QRectF"_hs)
        .ctor<qreal, qreal, qreal, qreal>()
        .data<&QRectF::setX, &QRectF::x>("x"_hs)
        .data<&QRectF::setY, &QRectF::y>("y"_hs)
        .data<&QRectF::setWidth, &QRectF::width>("width"_hs)
        .data<&QRectF::setHeight, &QRectF::height>("height"_hs)
        .conv<convert_qrectf>();

    entt::meta<QPointF>()
        .type("QPointF"_hs)
        .ctor<int, int>()
        .data<&QPointF::setX, &QPointF::x>("x"_hs)
        .data<&QPointF::setY, &QPointF::y>("y"_hs)
        .conv<convert_qpointf>();

    entt::meta<QUrl>() //
        .type("QUrl"_hs)
        .ctor<[](const std::string &url) { return QUrl{QString::fromStdString(url)}; }>()
        .data<nullptr, [](const QUrl &url) { return url.toDisplayString().toStdString(); }>("url"_hs)
        .conv<convert_qurl>();
}
} // namespace quite::probe
