#include "property_collector.hpp"
#include <QMetaProperty>
#include <ranges>
#include <QtQml/private/qqmldata_p.h>
#include <QtQml/private/qqmlmetatype_p.h>
#include <private/qv4executablecompilationunit_p.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <spdlog/spdlog.h>
#include "object_id.hpp"

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

std::pair<std::string, proto::Value> read_property(ObjectMeta &object_meta, const QMetaProperty &property)
{
    constexpr auto value_meta = QMetaType::fromType<proto::Value>();
    proto::Value value;
    const auto property_value = property.read(object_meta.object);
    if (property_value.canConvert<QObject *>())
    {
        spdlog::debug("prop {}={} convertable to QObject*", property.name(), property.typeName());
        value.mutable_object_val()->set_object_id(reinterpret_cast<probe::ObjectId>(property_value.value<QObject *>()));
    }
    else if (QQmlListReference qml_list{property_value};
             qml_list.isValid() and qml_list.canCount() and qml_list.canAt())
    {
        spdlog::debug("prop {}={} convertable to QQmlListReference", property.name(), property.typeName());
        const auto size = qml_list.count();
        for (qsizetype i = 0; i < size; i++)
        {
            auto &&obj = qml_list.at(i);
            value.mutable_array_val()->add_value()->mutable_object_val()->set_object_id(
                reinterpret_cast<std::uint64_t>(obj));
        }
    }
    else if (QMetaType::canConvert(property.metaType(), value_meta))
    {
        spdlog::debug("prop {}={} convertable with valueconverters", property.name(), property.typeName());
        QMetaType::convert(property.metaType(), &property_value, value_meta, &value);
    }
    else
    {
        spdlog::debug("prop {}={} not convertable", property.name(), property.typeName());
    }
    return {property.name(), std::move(value)};
}
namespace
{
void insert_value(std::unordered_map<std::string, proto::Value> *properties,
                  std::pair<std::string, proto::Value> property)
{
    properties->emplace(std::move(property));
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
            std::views::filter(can_be_read) |
            std::views::transform([&](auto &&prop) { return read_property(object_meta, prop); }),
        std::bind(insert_value, &properties, std::placeholders::_1));
    // Q: why doesn't a reference work here? Somehow a copy of the map will be created. Use a pointer for now.
    return properties;
}

} // namespace quite
