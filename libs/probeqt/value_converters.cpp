#include "value_converters.hpp"
#include <QColor>
#include <QMetaType>
#include <QObject>
#include <QQmlListProperty>
#include <QQmlListReference>
#include <QQuickItem>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <private/qquickanchors_p_p.h>
#include <quite/proto/types.pb.h>
#include "object_id.hpp"

namespace quite::probe
{

template <typename TBase, auto TFncPtr>
void register_trivial_converter()
{
    entt::meta<TBase>() //
        .template conv<[](const TBase &value) {
            proto::Value cnv;
            std::invoke(TFncPtr, cnv, value);
            return cnv;
        }>();
}

#define BEGIN_CNV_FNC(class_name)                                                                                      \
    proto::Value convert_##class_name(const class_name &data)                                                          \
    {                                                                                                                  \
        proto::Value value;                                                                                            \
        auto &&class_val = prepare_convert<class_name>(value);

#define END_CNV_FNC                                                                                                    \
    return value;                                                                                                      \
    }

using namespace entt::literals;

namespace
{
template <auto FAccessorFunc>
void cnv_class_member(proto::ClassValue *class_val, const auto &data, std::string_view member_name, auto &&...args)
{
    auto &&member = class_val->add_value();
    member->set_name(member_name);
    auto meta_val = entt::meta_any{std::invoke(FAccessorFunc, data, std::forward<decltype(args)...>(args)...)};
    if (meta_val.allow_cast<proto::Value>())
    {
        *member->mutable_value() = meta_val.cast<proto::Value>();
    }
}

template <typename T>
auto prepare_convert(proto::Value &value)
{
    constexpr auto kType = QMetaType::fromType<T>();

    auto &&class_val = value.mutable_class_val();
    class_val->set_type_name(kType.name());
    return class_val;
}

BEGIN_CNV_FNC(QRectF)
{
    cnv_class_member<&QRectF::x>(class_val, data, "x");
    cnv_class_member<&QRectF::y>(class_val, data, "y");
    cnv_class_member<&QRectF::width>(class_val, data, "width");
    cnv_class_member<&QRectF::height>(class_val, data, "height");
}
END_CNV_FNC

BEGIN_CNV_FNC(QRect)
{
    cnv_class_member<&QRect::x>(class_val, data, "x");
    cnv_class_member<&QRect::y>(class_val, data, "y");
    cnv_class_member<&QRect::width>(class_val, data, "width");
    cnv_class_member<&QRect::height>(class_val, data, "height");
}
END_CNV_FNC

BEGIN_CNV_FNC(QPointF)
{
    cnv_class_member<&QPointF::x>(class_val, data, "x");
    cnv_class_member<&QPointF::y>(class_val, data, "y");
}
END_CNV_FNC

BEGIN_CNV_FNC(QPoint)
{
    cnv_class_member<&QPoint::x>(class_val, data, "x");
    cnv_class_member<&QPoint::y>(class_val, data, "y");
}
END_CNV_FNC

BEGIN_CNV_FNC(QUrl)
{
    cnv_class_member<&QUrl::toDisplayString>(class_val, data, "url", QUrl::FormattingOptions{QUrl::PrettyDecoded});
}
END_CNV_FNC

BEGIN_CNV_FNC(QColor)
{
    cnv_class_member<&QColor::name>(class_val, data, "argb", QColor::NameFormat::HexArgb);
}
END_CNV_FNC

proto::Value convert_QQuickAnchorLine(const QQuickAnchorLine &data)
{
    entt::meta_any any_val{data.item};
    if (any_val.allow_cast<proto::Value>())
    {
        return any_val.cast<proto::Value>();
    }
    return proto::Value{};
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
    register_trivial_converter<quint8, &proto::Value::set_uint_val>();
    register_trivial_converter<quint16, &proto::Value::set_uint_val>();
    register_trivial_converter<quint32, &proto::Value::set_uint_val>();
    register_trivial_converter<quint64, &proto::Value::set_uint_val>();

    entt::meta<QObjectList>()
        .type("QObjectList*"_hs) //
        .conv<[](const QObjectList &values) {
            proto::Value cnv;
            for (auto &&value : std::as_const(values))
            {
                cnv.mutable_array_val()->add_value()->mutable_object_val()->set_object_id(
                    reinterpret_cast<std::uint64_t>(value));
            }
            return cnv;
        }>();

    entt::meta<QObject *>()
        .type("QObject*"_hs) //
        .conv<[](const QObject *obj) {
            proto::Value cnv;
            cnv.mutable_object_val()->set_object_id(reinterpret_cast<ObjectId>(obj));
            return cnv;
        }>();

    entt::meta<QQuickItem *>()
        .type("QQuickItem*"_hs) //
        .conv<[](const QObject *obj) {
            proto::Value cnv;
            cnv.mutable_object_val()->set_object_id(reinterpret_cast<ObjectId>(obj));
            return cnv;
        }>();

    entt::meta<QString>()
        .type("QString"_hs) //
        .ctor<[](const std::string &str) { return QString::fromStdString(str); }>()
        .conv<&QString::toStdString>()
        .conv<[](const QString &str) {
            proto::Value cnv;
            *cnv.mutable_string_val() = str.toStdString();
            return cnv;
        }>();

    entt::meta<QRect>()
        .type("QRect"_hs)
        .ctor<int, int, int, int>()
        .data<&QRect::setX, &QRect::x>("x"_hs)
        .data<&QRect::setY, &QRect::y>("y"_hs)
        .data<&QRect::setWidth, &QRect::width>("width"_hs)
        .data<&QRect::setHeight, &QRect::height>("height"_hs)
        .conv<convert_QRect>();

    entt::meta<QRectF>()
        .type("QRectF"_hs)
        .ctor<qreal, qreal, qreal, qreal>()
        .data<&QRectF::setX, &QRectF::x>("x"_hs)
        .data<&QRectF::setY, &QRectF::y>("y"_hs)
        .data<&QRectF::setWidth, &QRectF::width>("width"_hs)
        .data<&QRectF::setHeight, &QRectF::height>("height"_hs)
        .conv<convert_QRectF>();

    entt::meta<QPoint>()
        .type("QPoint"_hs)
        .ctor<int, int>()
        .data<&QPoint::setX, &QPoint::x>("x"_hs)
        .data<&QPoint::setY, &QPoint::y>("y"_hs)
        .conv<convert_QPoint>();

    entt::meta<QPointF>()
        .type("QPointF"_hs)
        .ctor<qreal, qreal>()
        .data<&QPointF::setX, &QPointF::x>("x"_hs)
        .data<&QPointF::setY, &QPointF::y>("y"_hs)
        .conv<convert_QPointF>();

    entt::meta<QUrl>() //
        .type("QUrl"_hs)
        .ctor<[](std::string_view url) { return QUrl{QAnyStringView{url}.toString()}; }>()
        .data<nullptr, [](const QUrl &url) { return url.toDisplayString().toStdString(); }>("url"_hs)
        .conv<convert_QUrl>();

    entt::meta<QColor>() //
        .type("QColor"_hs)
        .ctor<[](std::string_view hex_str) { return QColor::fromString(hex_str); }>()
        .data<nullptr, [](const QColor &col) { return col.name(); }>("name"_hs)
        .conv<convert_QColor>();

    entt::meta<QQuickAnchorLine>() //
        .type("QQuickAnchorLine"_hs)
        .data<&QQuickAnchorLine::item>("item"_hs)
        .conv<convert_QQuickAnchorLine>();
}
} // namespace quite::probe
