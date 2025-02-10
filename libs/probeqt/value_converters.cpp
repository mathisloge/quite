#include "value_converters.hpp"
#include <QColor>
#include <QList>
#include <QMetaType>
#include <QObject>
#include <QQmlListProperty>
#include <QQmlListReference>
#include <QQuickItem>
#include <entt/meta/container.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <private/qquickanchors_p_p.h>
#include <quite/logger.hpp>
#include <quite/proto/types.pb.h>
#include <quite/value/generic_value_class.hpp>
#include <quite/value/value_registry.hpp>
#include "meta_qt_containers.hpp"

DEFINE_LOGGER(value_converters)
using namespace entt::literals;
namespace quite::probe
{
namespace
{
template <typename T>
void register_type(ValueRegistry &value_registry, entt::hashed_string name)
{
    auto &meta_ctx = value_registry.context();
    entt::meta_factory<T>(meta_ctx) //
        .type(name.value())
        .template custom<QMetaType>(QMetaType::fromType<T>());
}
} // namespace
#define REGISTER_QT_TYPES_FUNCTION(TypeName, TypeId, Type) register_type<Type>(value_registry, #Type);

void register_converters(ValueRegistry &value_registry)
{
    auto &meta_ctx = value_registry.context();
    entt::meta_factory<QList<QObject *>>(meta_ctx)
        .type("QObjectList"_hs)
        .custom<QMetaType>(QMetaType::fromType<QObjectList>());

    QT_FOR_EACH_STATIC_PRIMITIVE_TYPE(REGISTER_QT_TYPES_FUNCTION);

    entt::meta_factory<QString>(meta_ctx) //
        .type("QString"_hs)
        .custom<QMetaType>(QMetaType::fromType<QString>())
        .conv<&QString::toStdString>();

    entt::meta_factory<QRect>(meta_ctx)
        .type("QRect"_hs)
        .custom<QMetaType>(QMetaType::fromType<QRect>())
        .data<&QRect::setX, &QRect::x>(value_registry.named_property("x"))
        .data<&QRect::setY, &QRect::y>(value_registry.named_property("y"))
        .data<&QRect::setWidth, &QRect::width>(value_registry.named_property("width"))
        .data<&QRect::setHeight, &QRect::height>(value_registry.named_property("height"));

    entt::meta_factory<QRectF>(meta_ctx)
        .type("QRectF"_hs)
        .custom<QMetaType>(QMetaType::fromType<QRectF>())
        .data<&QRectF::setX, &QRectF::x>(value_registry.named_property("x"))
        .data<&QRectF::setY, &QRectF::y>(value_registry.named_property("y"))
        .data<&QRectF::setWidth, &QRectF::width>(value_registry.named_property("width"))
        .data<&QRectF::setHeight, &QRectF::height>(value_registry.named_property("height"));

    entt::meta_factory<QPoint>(meta_ctx)
        .type("QPoint"_hs)
        .custom<QMetaType>(QMetaType::fromType<QPoint>())
        .data<&QPoint::setX, &QPoint::x>(value_registry.named_property("x"))
        .data<&QPoint::setY, &QPoint::y>(value_registry.named_property("y"));

    entt::meta_factory<QPointF>(meta_ctx)
        .type("QPointF"_hs)
        .custom<QMetaType>(QMetaType::fromType<QPointF>())
        .data<&QPointF::setX, &QPointF::x>(value_registry.named_property("x"))
        .data<&QPointF::setY, &QPointF::y>(value_registry.named_property("y"));

    entt::meta_factory<QUrl>(meta_ctx) //
        .type("QUrl"_hs)
        .custom<QMetaType>(QMetaType::fromType<QUrl>())
        .data<nullptr, [](const QUrl &url) { return url.url(); }>(value_registry.named_property("url"))
        .data<nullptr, [](const QUrl &url) { return url.toDisplayString(); }>(
            value_registry.named_property("displayString"));

    entt::meta_factory<QColor>(meta_ctx) //
        .type("QColor"_hs)
        .custom<QMetaType>(QMetaType::fromType<QColor>())
        .data<nullptr, [](const QColor &color) { return color.name(); }>(value_registry.named_property("name"))
        .data<&QColor::setAlpha, &QColor::alpha>(value_registry.named_property("alpha"))
        .data<&QColor::setRed, &QColor::red>(value_registry.named_property("red"))
        .data<&QColor::setGreen, &QColor::green>(value_registry.named_property("green"))
        .data<&QColor::setBlue, &QColor::blue>(value_registry.named_property("blue"));

    entt::meta_factory<QQuickAnchorLine>(meta_ctx) //
        .type("QQuickAnchorLine"_hs)
        .custom<QMetaType>(QMetaType::fromType<QQuickAnchorLine>())
        .data<&QQuickAnchorLine::item>(value_registry.named_property("item"));
}
} // namespace quite::probe
