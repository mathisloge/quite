#include "property_collector.hpp"
#include <QMetaProperty>
#include <ranges>
#include <QtQml/private/qqmldata_p.h>
#include <QtQml/private/qqmlmetatype_p.h>
#include <private/qv4executablecompilationunit_p.h>
#include <spdlog/spdlog.h>

namespace quite
{
ObjectMeta ObjectMeta::from_qobject(QObject *object)
{
    const QMetaObject *meta_object{nullptr};
    if (object->metaObject())
    {
        meta_object = object->metaObject();
        // auto collector = new QMetaPropertyCollector(obj);
    }
    else
    {
        auto data = QQmlData::get(object);
        if (not data or not data->compilationUnit)
        {
            spdlog::warn("got no data for qml object");
        }
        else
        {
            const auto qml_type = QQmlMetaType::qmlType(data->compilationUnit->url());
            if (qml_type.isValid())
            {
                meta_object = qml_type.metaObject();
            }
            else
            {
                spdlog::warn("qml type not valid");
            }
        }
    }
    return ObjectMeta{.object = object, .meta_object = meta_object};
}

namespace
{
proto::Value construct_value(const QMetaProperty &property)
{
    proto::Value value;

    spdlog::debug("prop {}={}", property.name(), property.typeName());

    // property.metaType();

    return value;
}

bool can_be_read(const QMetaProperty &prop)
{
    return not(prop.name() == std::string_view{"inputDirection"} or prop.name() == std::string_view{"locale"} or
               prop.name() == std::string_view{"fontInfo"});
}
} // namespace

std::unordered_map<std::string, proto::Value> collect_properties(ObjectMeta object_meta)
{
    std::unordered_map<std::string, proto::Value> properties;

    std::ranges::for_each(
        std::ranges::iota_view(0, object_meta.meta_object->propertyCount()) |
            std::views::transform([&](int prop_idx) { return object_meta.meta_object->property(prop_idx); }) |
            std::views::filter([](const QMetaProperty &prop) { return prop.isValid() and prop.isReadable(); }) |
            std::views::filter(can_be_read),
        construct_value);

    return properties;
}

void test(ObjectMeta object_meta)
{}

} // namespace quite
