#include "property_collector.hpp"
#include <QMetaProperty>
#include <ranges>
#include <QtQml/private/qqmldata_p.h>
#include <QtQml/private/qqmlmetatype_p.h>
#include <private/qv4executablecompilationunit_p.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
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
void insert_value(std::unordered_map<std::string, proto::Value> *properties,
                  ObjectMeta &object_meta,
                  const QMetaProperty &property)
{
    constexpr auto value_meta = QMetaType::fromType<proto::Value>();
    proto::Value value;
    const bool convertable = QMetaType::canConvert(property.metaType(), value_meta);
    spdlog::debug("prop {}={} convertable={}", property.name(), property.typeName(), convertable);
    if (convertable)
    {
        const auto property_value = property.read(object_meta.object);
        QMetaType::convert(property.metaType(), &property_value, value_meta, &value);
    }
    else
    {
        *value.mutable_class_val()->mutable_type_name() = property.typeName();
    }
    properties->emplace(property.name(), std::move(value));
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
        std::bind(insert_value, &properties, object_meta, std::placeholders::_1));
    // Q: why doesn't a reference work here? Somehow a copy of the map will be created. Use a pointer for now.
    return properties;
}

} // namespace quite
