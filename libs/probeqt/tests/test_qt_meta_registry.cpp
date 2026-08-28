// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QMetaType>
#include <QObject>
#include <gtest/gtest.h>
#include <stdexec/execution.hpp>
#include "qt_meta_registry.hpp"

using namespace quite;
using namespace quite::probe;
using namespace quite::meta;

namespace
{
class MetaRegistryGadget
{
    Q_GADGET
    Q_PROPERTY(Color color MEMBER color_)
  public:
    enum class Color
    {
        Red,
        Green,
        Blue
    };
    Q_ENUM(Color)

  private:
    Color color_{Color::Red};
};

Type lookup(meta::TypeId id)
{
    QtMetaRegistry registry;
    auto [result] = stdexec::sync_wait(registry.lookup_type(id)).value();
    return std::move(result).value();
}
} // namespace

TEST(QtMetaRegistry, ResolvesIntPrimitive)
{
    const auto type = lookup(static_cast<meta::TypeId>(QMetaType::fromType<int>().id()));
    ASSERT_TRUE(std::holds_alternative<PrimitiveType>(type));
    EXPECT_EQ(std::get<PrimitiveType>(type), PrimitiveType::type_int);
}

TEST(QtMetaRegistry, ResolvesStringPrimitive)
{
    const auto type = lookup(static_cast<meta::TypeId>(QMetaType::fromType<QString>().id()));
    ASSERT_TRUE(std::holds_alternative<PrimitiveType>(type));
    EXPECT_EQ(std::get<PrimitiveType>(type), PrimitiveType::type_string);
}

TEST(QtMetaRegistry, ResolvesEnumWithValues)
{
    const auto type = lookup(static_cast<meta::TypeId>(QMetaType::fromType<MetaRegistryGadget::Color>().id()));
    ASSERT_TRUE(std::holds_alternative<EnumTypePtr>(type));
    const auto &enum_type = *std::get<EnumTypePtr>(type);
    EXPECT_EQ(enum_type.values.at("Red"), 0);
    EXPECT_EQ(enum_type.values.at("Green"), 1);
    EXPECT_EQ(enum_type.values.at("Blue"), 2);
}

TEST(QtMetaRegistry, ResolvesGadgetAsObjectTypeWithProperties)
{
    const auto type = lookup(static_cast<meta::TypeId>(QMetaType::fromType<MetaRegistryGadget>().id()));
    ASSERT_TRUE(std::holds_alternative<ObjectTypePtr>(type));
    const auto &obj_type = *std::get<ObjectTypePtr>(type);
    EXPECT_EQ(obj_type.name, "MetaRegistryGadget");
    ASSERT_EQ(obj_type.properties.size(), 1u);
    EXPECT_EQ(obj_type.properties[0].name, "color");
}

TEST(QtMetaRegistry, UnknownTypeIdReturnsNotFound)
{
    QtMetaRegistry registry;
    auto [result] = stdexec::sync_wait(registry.lookup_type(static_cast<meta::TypeId>(999999999))).value();
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error().code, ErrorCode::not_found);
}

#include "test_qt_meta_registry.moc"
