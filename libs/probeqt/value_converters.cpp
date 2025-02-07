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
#include <quite/logger.hpp>
#include <quite/proto/traits.hpp>
#include <quite/proto/types.pb.h>
#include "object_id.hpp"
#include "qt_meta_type_accessor.hpp"

DEFINE_LOGGER(value_converters)

using namespace entt::literals;

namespace quite::probe
{
#define BEGIN_CNV_FNC(class_name)                                                                                      \
    proto::Value convert_##class_name(const class_name &data)                                                          \
    {                                                                                                                  \
        proto::Value value;                                                                                            \
        add_type_id_from_type<class_name>(value);                                                                      \
        auto &&class_val = prepare_convert<class_name>(value);

#define END_CNV_FNC                                                                                                    \
    return value;                                                                                                      \
    }

namespace
{
template <typename T>
void add_type_id_from_type(proto::Value &val)
{
    val.set_type_id(QMetaType::fromType<T>().id());
}

void add_type_id_from_instance(auto &&instance, proto::Value &val)
{
    const auto meta_type = try_get_qt_meta_type(instance);
    if (meta_type.isValid())
    {
        val.set_type_id(meta_type.id());
    }
    else
    {
        LOG_ERROR(value_converters(), "Could not get a meta type for value.");
    }
}

template <typename TBase, auto TFncPtr>
void register_trivial_converter()
{
    entt::meta_factory<TBase>() //
        .template func<[]() { return QMetaType::fromType<TBase>(); }>("metaType"_hs)
        .template conv<[](const TBase &value) {
            proto::Value cnv;
            add_type_id_from_type<TBase>(cnv);
            std::invoke(TFncPtr, cnv, value);
            return cnv;
        }>();
}

template <auto FAccessorFunc>
void cnv_class_member(proto::ClassValue *class_val, const auto &data, std::string_view member_name, auto &&...args)
{
    auto &&member = class_val->add_value();
    member->set_name(member_name.data());
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
    add_type_id_from_type<T>(value);
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

    entt::meta_factory<QObjectList>()
        .type("QObjectList*"_hs) //
        .func<[]() { return QMetaType::fromType<QObjectList>(); }>("metaType"_hs)
        .conv<[](const QObjectList &values) {
            proto::Value cnv;
            add_type_id_from_type<QObjectList>(cnv);
            for (auto &&value : std::as_const(values))
            {
                cnv.mutable_array_val()->add_value()->mutable_object_val()->set_object_id(
                    reinterpret_cast<std::uint64_t>(value));
            }
            return cnv;
        }>();

    entt::meta_factory<QObject *>()
        .type("QObject*"_hs) //
        .func<[](const QObject *obj) { return obj->metaObject()->metaType(); }>("metaType"_hs)
        .conv<[](const QObject *obj) {
            proto::Value cnv;
            add_type_id_from_instance(obj, cnv);
            cnv.mutable_object_val()->set_object_id(reinterpret_cast<ObjectId>(obj));
            return cnv;
        }>();

    entt::meta_factory<QQuickItem *>()
        .type("QQuickItem*"_hs) //
        .func<[]() { return QMetaType::fromType<QQuickItem *>(); }>("metaType"_hs)
        .conv<[](const QQuickItem *obj) {
            proto::Value cnv;
            add_type_id_from_instance(obj, cnv);
            cnv.mutable_object_val()->set_object_id(reinterpret_cast<ObjectId>(obj));
            return cnv;
        }>();

    entt::meta_factory<QString>()
        .type("QString"_hs) //
        .ctor<[](const std::string &str) { return QString::fromStdString(str); }>()
        .func<[]() { return QMetaType::fromType<QString>(); }>("metaType"_hs)
        .conv<&QString::toStdString>()
        .conv<[](const QString &str) {
            proto::Value cnv;
            add_type_id_from_type<QString>(cnv);
            *cnv.mutable_string_val() = str.toStdString();
            return cnv;
        }>();

    entt::meta_factory<QRect>()
        .type("QRect"_hs)
        .ctor<int, int, int, int>()
        .data<&QRect::setX, &QRect::x>("x"_hs)
        .data<&QRect::setY, &QRect::y>("y"_hs)
        .data<&QRect::setWidth, &QRect::width>("width"_hs)
        .data<&QRect::setHeight, &QRect::height>("height"_hs)
        .func<[]() { return QMetaType::fromType<QRect>(); }>("metaType"_hs)
        .conv<convert_QRect>();

    entt::meta_factory<QRectF>()
        .type("QRectF"_hs)
        .ctor<qreal, qreal, qreal, qreal>()
        .data<&QRectF::setX, &QRectF::x>("x"_hs)
        .data<&QRectF::setY, &QRectF::y>("y"_hs)
        .data<&QRectF::setWidth, &QRectF::width>("width"_hs)
        .data<&QRectF::setHeight, &QRectF::height>("height"_hs)
        .func<[]() { return QMetaType::fromType<QRectF>(); }>("metaType"_hs)
        .conv<convert_QRectF>();

    entt::meta_factory<QPoint>()
        .type("QPoint"_hs)
        .ctor<int, int>()
        .data<&QPoint::setX, &QPoint::x>("x"_hs)
        .data<&QPoint::setY, &QPoint::y>("y"_hs)
        .func<[]() { return QMetaType::fromType<QPoint>(); }>("metaType"_hs)
        .conv<convert_QPoint>();

    entt::meta_factory<QPointF>()
        .type("QPointF"_hs)
        .ctor<qreal, qreal>()
        .data<&QPointF::setX, &QPointF::x>("x"_hs)
        .data<&QPointF::setY, &QPointF::y>("y"_hs)
        .func<[]() { return QMetaType::fromType<QPointF>(); }>("metaType"_hs)
        .conv<convert_QPointF>();

    entt::meta_factory<QUrl>() //
        .type("QUrl"_hs)
        .ctor<[](std::string_view url) { return QUrl{QAnyStringView{url}.toString()}; }>()
        .data<nullptr, [](const QUrl &url) { return url.toDisplayString().toStdString(); }>("url"_hs)
        .func<[]() { return QMetaType::fromType<QUrl>(); }>("metaType"_hs)
        .conv<convert_QUrl>();

    entt::meta_factory<QColor>() //
        .type("QColor"_hs)
        .ctor<[](std::string_view hex_str) { return QColor::fromString(hex_str); }>()
        .data<nullptr, [](const QColor &col) { return col.name(); }>("name"_hs)
        .func<[]() { return QMetaType::fromType<QColor>(); }>("metaType"_hs)
        .conv<convert_QColor>();

    entt::meta_factory<QQuickAnchorLine>() //
        .type("QQuickAnchorLine"_hs)
        .data<&QQuickAnchorLine::item>("item"_hs)
        .func<[]() { return QMetaType::fromType<QQuickAnchorLine>(); }>("metaType"_hs)
        .conv<convert_QQuickAnchorLine>();

    entt::meta_factory<GenericQtClass>()
        .type("GenericQtClass"_hs)
        .data<&GenericQtClass::properties>("properties"_hs)
        .traits(proto::Traits::unpack_properties);
}
} // namespace quite::probe
