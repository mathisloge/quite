// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QColor>
#include <QCoreApplication>
#include <QList>
#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QRectF>
#include <QString>
#include <QUrl>
#include <boost/ut.hpp>
#include <entt/meta/meta.hpp>
#include <entt/meta/resolve.hpp>
#include <quite/value/value_registry.hpp>
#include "value_converters.hpp"

using namespace quite;
using namespace quite::probe;
using namespace boost::ut;
using namespace entt::literals;

static suite<"qtprobe value converters"> _ = [] { // NOLINT
    "register_converters registers QString"_test = [] {
        ValueRegistry registry;
        register_converters(registry);

        auto meta = entt::resolve("QString"_hs);
        expect(static_cast<bool>(meta));
        QString s = "abc";
        auto any = entt::forward_as_meta(s);
        expect(any.type() == meta);
        expect(any.cast<QString>().toStdString() == std::string("abc"));
    };

    "register_converters registers QRect"_test = [] {
        ValueRegistry registry;
        register_converters(registry);

        auto meta = entt::resolve("QRect"_hs);
        expect(static_cast<bool>(meta));
        QRect rect(1, 2, 3, 4);
        auto any = entt::forward_as_meta(rect);
        expect(any.type() == meta);
        expect(any.cast<QRect>() == rect);
    };

    "register_converters registers QPoint"_test = [] {
        ValueRegistry registry;
        register_converters(registry);

        auto meta = entt::resolve("QPoint"_hs);
        expect(static_cast<bool>(meta));
        QPoint pt(5, 7);
        auto any = entt::forward_as_meta(pt);
        expect(any.type() == meta);
        expect(any.cast<QPoint>() == pt);
    };

    "register_converters registers QPointF"_test = [] {
        ValueRegistry registry;
        register_converters(registry);

        auto meta = entt::resolve("QPointF"_hs);
        expect(static_cast<bool>(meta));
        QPointF ptf(1.5, 2.5);
        auto any = entt::forward_as_meta(ptf);
        expect(any.type() == meta);
        expect(any.cast<QPointF>() == ptf);
    };

    "register_converters registers QRectF"_test = [] {
        ValueRegistry registry;
        register_converters(registry);

        auto meta = entt::resolve("QRectF"_hs);
        expect(static_cast<bool>(meta));
        QRectF rectf(1.1, 2.2, 3.3, 4.4);
        auto any = entt::forward_as_meta(rectf);
        expect(any.type() == meta);
        expect(any.cast<QRectF>() == rectf);
    };

    "register_converters registers QColor"_test = [] {
        ValueRegistry registry;
        register_converters(registry);

        auto meta = entt::resolve("QColor"_hs);
        expect(static_cast<bool>(meta));
        QColor color(Qt::red);
        auto any = entt::forward_as_meta(color);
        expect(any.type() == meta);
        expect(any.cast<QColor>() == color);
    };

    "register_converters registers QUrl"_test = [] {
        ValueRegistry registry;
        register_converters(registry);

        auto meta = entt::resolve("QUrl"_hs);
        expect(static_cast<bool>(meta));
        QUrl url("https://github.com/mathisloge/quite");
        auto any = entt::forward_as_meta(url);
        expect(any.type() == meta);
        expect(any.cast<QUrl>() == url);
    };

    "register_converters registers QObjectList"_test = [] {
        ValueRegistry registry;
        register_converters(registry);

        auto meta = entt::resolve("QObjectList"_hs);
        expect(static_cast<bool>(meta));
        QList<QObject *> list;
        QObject obj;
        list.append(&obj);
        list.append(&obj);
        auto any = entt::forward_as_meta(list);
        expect(any.type() == meta);
        expect(any.cast<QList<QObject *>>().size() == 2);
    };

    // Macro for testing registration of a type by name and a value
#define TEST_PRIMITIVE_TYPE(TypeName, TypeId, Type)                                                                    \
    {                                                                                                                  \
        auto meta = entt::resolve(#Type##_hs);                                                                         \
        expect(static_cast<bool>(meta));                                                                               \
        auto any = entt::forward_as_meta((Type){});                                                                    \
        expect(any.type() == meta);                                                                                    \
        expect(any.cast<Type>() == (Type){});                                                                          \
    }
    "register_converters registers all static primitive types"_test = [] {
        ValueRegistry registry;
        register_converters(registry);

        QT_FOR_EACH_STATIC_PRIMITIVE_NON_VOID_TYPE(TEST_PRIMITIVE_TYPE);
    };
};
