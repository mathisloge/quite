#include "property_collector.hpp"
#include <QMetaProperty>
#include <ranges>
#include <QtQml/private/qqmldata_p.h>
#include <QtQml/private/qqmlmetatype_p.h>
#include <entt/meta/factory.hpp>
#include <private/qv4executablecompilationunit_p.h>
#include <quite/logger.hpp>

DEFINE_LOGGER(property_collector_logger)
namespace quite
{
namespace
{
void insert_value(std::unordered_map<std::string, proto::Value> *properties,
                  std::pair<std::string, proto::Value> property)
{
    properties->emplace(std::move(property));
}
} // namespace

ObjectMeta ObjectMeta::from_qobject(QObject *object)
{
    const QMetaObject *meta_object{nullptr};
    if (object->metaObject() != nullptr)
    {
        meta_object = object->metaObject();
    }
    else
    {
        auto &&data = QQmlData::get(object);
        if (data != nullptr or not data->compilationUnit)
        {
            LOG_WARNING(property_collector_logger, "got no data for qml object");
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
                LOG_WARNING(property_collector_logger, "qml type not valid");
            }
        }
    }
    return ObjectMeta{.object = object, .meta_object = meta_object};
}

std::pair<std::string, proto::Value> read_property(const QVariant property_value, const QMetaProperty &property)
{
    proto::Value value;

    // important: check for explicit conversions first. E.g. QQuickAnchorLine is a QGadget but should be converted with
    // the explicit converter.
    if (auto custom_meta_type = entt::resolve(entt::hashed_string{property.metaType().name()}.value());
        custom_meta_type)
    {
        auto &&any_obj = custom_meta_type.from_void(&property_value);
        if (any_obj.allow_cast<proto::Value>())
        {
            LOG_DEBUG(property_collector_logger,
                      "prop {}({}) convertible via meta",
                      property.name(),
                      property.metaType().name());
            value = any_obj.cast<proto::Value>();
        }
        else
        {
            LOG_ERROR(property_collector_logger, "could not cast {} to proto::Value", property.metaType().name());
        }
    }
    else if (property.metaType().flags().testAnyFlags(QMetaType::IsGadget | QMetaType::PointerToGadget))
    {
        auto &&gadget_metaobj = property.metaType().metaObject();
        LOG_DEBUG(property_collector_logger,
                  "prop {}={} convertable to QGadget (props={})",
                  property.name(),
                  property.typeName(),
                  gadget_metaobj->propertyCount());
        auto &&class_val = value.mutable_class_val();
        class_val->set_type_name(property.typeName());

        const auto add_val_to_class = [&](std::pair<std::string, proto::Value> property) {
            auto &&val = class_val->add_value();
            val->set_name(std::move(property.first));
            *val->mutable_value() = std::move(property.second);
        };
        std::ranges::for_each(
            std::ranges::iota_view(0, gadget_metaobj->propertyCount()) |
                std::views::transform([&](int prop_idx) { return gadget_metaobj->property(prop_idx); }) |
                std::views::filter([](const QMetaProperty &prop) { return prop.isValid() and prop.isReadable(); }) |
                std::views::transform([&](auto &&prop) {
                    return std::tuple{prop.readOnGadget(property_value.data()), std::forward<decltype(prop)>(prop)};
                }) |
                std::views::transform([&](auto &&prop) { return read_property(std::get<0>(prop), std::get<1>(prop)); }),
            add_val_to_class);
    }
    else if (QQmlListReference qml_list{property_value};
             qml_list.isValid() and qml_list.canCount() and qml_list.canAt())
    {
        LOG_DEBUG(property_collector_logger,
                  "prop {}={} convertable to QQmlListReference",
                  property.name(),
                  property.typeName());
        const auto size = qml_list.count();
        for (qsizetype i = 0; i < size; i++)
        {
            auto &&obj = qml_list.at(i);
            value.mutable_array_val()->add_value()->mutable_object_val()->set_object_id(
                reinterpret_cast<std::uint64_t>(obj));
        }
    }
    else
    {
        LOG_DEBUG(property_collector_logger, "prop {}={} not convertable", property.name(), property.typeName());
    }
    return {property.name(), std::move(value)};
}

std::unordered_map<std::string, proto::Value> collect_properties(ObjectMeta object_meta)
{
    std::unordered_map<std::string, proto::Value> properties;

    std::ranges::for_each(
        std::ranges::iota_view(0, object_meta.meta_object->propertyCount()) | //
            std::views::transform([&](int prop_idx) { return object_meta.meta_object->property(prop_idx); }) |
            std::views::filter([](auto &&prop) { return prop.isValid() and prop.isReadable(); }) |
            std::views::transform([&](auto &&prop) {
                return std::tuple{prop.read(object_meta.object), std::forward<decltype(prop)>(prop)};
            }) |
            std::views::transform([&](auto &&prop) { return read_property(std::get<0>(prop), std::get<1>(prop)); }),
        std::bind(insert_value, &properties, std::placeholders::_1));
    // Q: why doesn't a reference work here? Somehow a copy of the map will be created. Use a pointer for now.
    return properties;
}

} // namespace quite
