// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QMetaProperty>
#include <QObject>
#include <QString>
#include <QVariant>
#include <gtest/gtest.h>
#include <quite/error.hpp>
#include <quite/value/object_query.hpp>
#include "property_collector.hpp"
#include "quite/value/generic_value_class.hpp"

using namespace quite;

namespace
{
class SimpleObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int number MEMBER m_number)
    Q_PROPERTY(QString text MEMBER m_text)
  public:
    int m_number{42};
    QString m_text{"hello"};
};

class SimpleQGadget
{
    Q_GADGET
    Q_PROPERTY(Color color MEMBER color_)
    Q_PROPERTY(Color2 color2 MEMBER color2_)
  public:
    enum class Color
    {
        Red,
        Green,
        Blue
    };
    Q_ENUM(Color)

    enum class Color2 : quint64
    {
        Red,
        Green,
        Blue
    };
    Q_ENUM(Color2)

  private:
    Color color_;
    Color2 color2_;
};

} // namespace

TEST(PropertyCollector, ReadPropertyReturnsCorrectIntAndString)
{
    SimpleObject obj;
    const QMetaObject *meta = obj.metaObject();

    // int property
    int number_idx = meta->indexOfProperty("number");
    QMetaProperty number_prop = meta->property(number_idx);
    auto [name1, value1] = read_property(obj.property("number"), number_prop);
    EXPECT_EQ(name1, "number");
    EXPECT_EQ(value1.cast<int>(), 42);

    // QString property
    int text_idx = meta->indexOfProperty("text");
    QMetaProperty text_prop = meta->property(text_idx);
    auto [name2, value2] = read_property(obj.property("text"), text_prop);
    EXPECT_EQ(name2, "text");
    EXPECT_EQ(value2.cast<QString>().toStdString(), "hello");
}

TEST(PropertyCollector, CollectPropertiesReturnsAllProperties)
{
    SimpleObject obj;
    auto meta = ObjectMeta::from_qobject(&obj);

    // Collect all properties
    auto props = collect_properties(meta, {});
    EXPECT_TRUE(props.contains("number"));
    EXPECT_TRUE(props.contains("text"));
    EXPECT_EQ(props["number"].cast<int>(), 42);
    EXPECT_EQ(props["text"].cast<QString>().toStdString(), "hello");
}

TEST(PropertyCollector, CollectPropertiesFiltersByPropertyNames)
{
    SimpleObject obj;
    auto meta = ObjectMeta::from_qobject(&obj);

    std::vector<std::string> names = {"text"};
    auto props = collect_properties(meta, names);
    EXPECT_FALSE(props.contains("number"));
    EXPECT_TRUE(props.contains("text"));
    EXPECT_EQ(props["text"].cast<QString>().toStdString(), "hello");
}

TEST(PropertyCollector, ConvertVoidPtrToAnyOfQGadgetWithEnumValues)
{
    SimpleQGadget obj{};

    auto any_obj = convert_void_ptr_to_any(obj.staticMetaObject.metaType(), &obj);
    ASSERT_TRUE(any_obj.allow_cast<GenericClass>());
    auto generic_class = any_obj.cast<GenericClass>();

    ASSERT_TRUE(generic_class.properties.contains("color"));
    EXPECT_TRUE(generic_class.properties["color"].allow_cast<std::int64_t>());

    ASSERT_TRUE(generic_class.properties.contains("color2"));
    EXPECT_TRUE(generic_class.properties["color2"].allow_cast<std::uint64_t>());
}

#include "test_property_collector.moc"
