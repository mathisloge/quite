// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
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
#include <entt/meta/meta.hpp>
#include <entt/meta/resolve.hpp>
#include <gtest/gtest.h>
#include <quite/value/value_registry.hpp>
#include "value_converters.hpp"

using namespace quite;
using namespace quite::probe;
using namespace entt::literals;

TEST(ValueConverters, RegistersQString)
{
    ValueRegistry registry;
    register_converters(registry);

    auto meta = entt::resolve("QString"_hs);
    EXPECT_TRUE(static_cast<bool>(meta));
    QString s = "abc";
    auto any = entt::forward_as_meta(s);
    EXPECT_EQ(any.type(), meta);
    EXPECT_EQ(any.cast<QString>().toStdString(), std::string("abc"));
}

TEST(ValueConverters, RegistersQRect)
{
    ValueRegistry registry;
    register_converters(registry);

    auto meta = entt::resolve("QRect"_hs);
    EXPECT_TRUE(static_cast<bool>(meta));
    QRect rect(1, 2, 3, 4);
    auto any = entt::forward_as_meta(rect);
    EXPECT_EQ(any.type(), meta);
    EXPECT_EQ(any.cast<QRect>(), rect);
}

TEST(ValueConverters, RegistersQPoint)
{
    ValueRegistry registry;
    register_converters(registry);

    auto meta = entt::resolve("QPoint"_hs);
    EXPECT_TRUE(static_cast<bool>(meta));
    QPoint pt(5, 7);
    auto any = entt::forward_as_meta(pt);
    EXPECT_EQ(any.type(), meta);
    EXPECT_EQ(any.cast<QPoint>(), pt);
}

TEST(ValueConverters, RegistersQPointF)
{
    ValueRegistry registry;
    register_converters(registry);

    auto meta = entt::resolve("QPointF"_hs);
    EXPECT_TRUE(static_cast<bool>(meta));
    QPointF ptf(1.5, 2.5);
    auto any = entt::forward_as_meta(ptf);
    EXPECT_EQ(any.type(), meta);
    EXPECT_EQ(any.cast<QPointF>(), ptf);
}

TEST(ValueConverters, RegistersQRectF)
{
    ValueRegistry registry;
    register_converters(registry);

    auto meta = entt::resolve("QRectF"_hs);
    EXPECT_TRUE(static_cast<bool>(meta));
    QRectF rectf(1.1, 2.2, 3.3, 4.4);
    auto any = entt::forward_as_meta(rectf);
    EXPECT_EQ(any.type(), meta);
    EXPECT_EQ(any.cast<QRectF>(), rectf);
}

TEST(ValueConverters, RegistersQColor)
{
    ValueRegistry registry;
    register_converters(registry);

    auto meta = entt::resolve("QColor"_hs);
    EXPECT_TRUE(static_cast<bool>(meta));
    QColor color(Qt::red);
    auto any = entt::forward_as_meta(color);
    EXPECT_EQ(any.type(), meta);
    EXPECT_EQ(any.cast<QColor>(), color);
}

TEST(ValueConverters, RegistersQUrl)
{
    ValueRegistry registry;
    register_converters(registry);

    auto meta = entt::resolve("QUrl"_hs);
    EXPECT_TRUE(static_cast<bool>(meta));
    QUrl url("https://github.com/mathisloge/quite");
    auto any = entt::forward_as_meta(url);
    EXPECT_EQ(any.type(), meta);
    EXPECT_EQ(any.cast<QUrl>(), url);
}

TEST(ValueConverters, RegistersQObjectList)
{
    ValueRegistry registry;
    register_converters(registry);

    auto meta = entt::resolve("QObjectList"_hs);
    EXPECT_TRUE(static_cast<bool>(meta));
    QList<QObject *> list;
    QObject obj;
    list.append(&obj);
    list.append(&obj);
    auto any = entt::forward_as_meta(list);
    EXPECT_EQ(any.type(), meta);
    EXPECT_EQ(any.cast<QList<QObject *>>().size(), 2);
}

// Macro for testing registration of a type by name and a value
#define TEST_PRIMITIVE_TYPE(TypeName, TypeId, Type)                                                                    \
    {                                                                                                                  \
        auto meta = entt::resolve(#Type##_hs);                                                                         \
        EXPECT_TRUE(static_cast<bool>(meta));                                                                          \
        auto any = entt::forward_as_meta((Type){});                                                                    \
        EXPECT_EQ(any.type(), meta);                                                                                   \
        EXPECT_EQ(any.cast<Type>(), (Type){});                                                                         \
    }
TEST(ValueConverters, RegistersAllStaticPrimitiveTypes)
{
    ValueRegistry registry;
    register_converters(registry);

    QT_FOR_EACH_STATIC_PRIMITIVE_NON_VOID_TYPE(TEST_PRIMITIVE_TYPE);
}
