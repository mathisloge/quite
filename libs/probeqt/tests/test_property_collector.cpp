// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include <QEventLoop>
#include <QMetaProperty>
#include <QObject>
#include <QString>
#include <QVariant>
#include <boost/ut.hpp>
#include <quite/error.hpp>
#include <quite/value/object_query.hpp>
#include "property_collector.hpp"
#include "quite/value/generic_value_class.hpp"

using namespace quite;
using namespace boost::ut;
using namespace std::literals::string_view_literals;

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

    enum class Color2 : std::uint64_t
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

static suite<"qtprobe propertycollector"> _ = [] { // NOLINT
    "read_property returns correct int and string"_test = [] {
        SimpleObject obj;
        const QMetaObject *meta = obj.metaObject();

        // int property
        int number_idx = meta->indexOfProperty("number");
        QMetaProperty number_prop = meta->property(number_idx);
        auto [name1, value1] = read_property(obj.property("number"), number_prop);
        expect(name1 == "number");
        expect(value1.cast<int>() == 42);

        // QString property
        int text_idx = meta->indexOfProperty("text");
        QMetaProperty text_prop = meta->property(text_idx);
        auto [name2, value2] = read_property(obj.property("text"), text_prop);
        expect(name2 == "text");
        expect(value2.cast<QString>().toStdString() == "hello"sv);
    };

    "collect_properties returns all properties"_test = [] {
        SimpleObject obj;
        auto meta = ObjectMeta::from_qobject(&obj);

        // Collect all properties
        auto props = collect_properties(meta, {});
        expect(props.contains("number"));
        expect(props.contains("text"));
        expect(props["number"].cast<int>() == 42);
        expect(props["text"].cast<QString>().toStdString() == "hello"sv);
    };

    "collect_properties filters by property_names"_test = [] {
        SimpleObject obj;
        auto meta = ObjectMeta::from_qobject(&obj);

        std::vector<std::string> names = {"text"};
        auto props = collect_properties(meta, names);
        expect(!props.contains("number"));
        expect(props.contains("text"));
        expect(props["text"].cast<QString>().toStdString() == "hello"sv);
    };

    "convert_void_ptr_to_any of an QGadget with enum values"_test = [] {
        SimpleQGadget obj{};

        auto any_obj = convert_void_ptr_to_any(obj.staticMetaObject.metaType(), &obj);
        expect(any_obj.allow_cast<GenericClass>());
        auto generic_class = any_obj.cast<GenericClass>();

        expect(generic_class.properties.contains("color"));
        expect(generic_class.properties["color"].allow_cast<std::int64_t>());

        expect(generic_class.properties.contains("color2"));
        expect(generic_class.properties["color2"].allow_cast<std::uint64_t>());
    };
};

#include "test_property_collector.moc"
