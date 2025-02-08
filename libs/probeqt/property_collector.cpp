#include "property_collector.hpp"
#include <QMetaProperty>
#include <QQmlListReference>
#include <ranges>
#include <entt/meta/factory.hpp>
#include <quite/logger.hpp>
#include <quite/value/generic_value_class.hpp>
#include "qt_meta_type_accessor.hpp"
#include "value_converters.hpp"

DEFINE_LOGGER(property_collector_logger)
namespace quite
{
ObjectMeta ObjectMeta::from_qobject(QObject *object)
{
    return ObjectMeta{.object = object, .meta_object = probe::try_get_qt_meta_object(object)};
}

std::pair<std::string, entt::meta_any> read_property(const QVariant property_value, const QMetaProperty &property)
{
    entt::meta_any value;

    // important: check for explicit conversions first. E.g. QQuickAnchorLine is a QGadget but should be converted with
    // the explicit converter.
    if (auto custom_meta_type = entt::resolve(entt::hashed_string{property.metaType().name()}.value());
        custom_meta_type)
    {
        value = custom_meta_type.from_void(&property_value);
    }
    else if (property.metaType().flags().testAnyFlags(QMetaType::IsGadget | QMetaType::PointerToGadget))
    {
        auto &&gadget_metaobj = property.metaType().metaObject();
        LOG_DEBUG(property_collector_logger(),
                  "prop {}={} convertable to QGadget (props={})",
                  property.name(),
                  property.typeName(),
                  gadget_metaobj->propertyCount());
        GenericClass generic_class;
        auto view =
            std::ranges::iota_view(0, gadget_metaobj->propertyCount()) |
            std::views::transform([&](int prop_idx) { return gadget_metaobj->property(prop_idx); }) |
            std::views::filter([](const QMetaProperty &prop) { return prop.isValid() and prop.isReadable(); }) |
            std::views::transform([&](auto &&prop) {
                return std::tuple{prop.readOnGadget(property_value.data()), std::forward<decltype(prop)>(prop)};
            }) |
            std::views::transform([&](auto &&prop) { return read_property(std::get<0>(prop), std::get<1>(prop)); });
        for (auto &&name_value : view)
        {
            generic_class.properties.emplace(std::forward<decltype(name_value)>(name_value));
        }
        value = std::move(generic_class);
    }
    else if (QQmlListReference qml_list{property_value};
             qml_list.isValid() and qml_list.canCount() and qml_list.canAt())
    {
        LOG_DEBUG(property_collector_logger(),
                  "prop {}={} convertable to QQmlListReference",
                  property.name(),
                  property.typeName());
        const auto size = qml_list.count();
        std::vector<entt::meta_any> object_list;
        object_list.reserve(size);
        for (qsizetype i = 0; i < size; i++)
        {
            auto &&obj = qml_list.at(i);
            object_list.emplace_back(obj);
        }
        value = std::move(object_list);
    }
    else
    {
        LOG_DEBUG(property_collector_logger(), "prop {}={} not convertable", property.name(), property.typeName());
    }
    return {property.name(), std::move(value)};
}

std::unordered_map<std::string, entt::meta_any> collect_properties(ObjectMeta object_meta)
{
    std::unordered_map<std::string, entt::meta_any> properties;

    auto view = std::ranges::iota_view(0, object_meta.meta_object->propertyCount()) | //
                std::views::transform([&](int prop_idx) { return object_meta.meta_object->property(prop_idx); }) |
                std::views::filter([](auto &&prop) { return prop.isValid() and prop.isReadable(); }) |
                std::views::transform([&](auto &&prop) {
                    return std::tuple{prop.read(object_meta.object), std::forward<decltype(prop)>(prop)};
                }) |
                std::views::transform([&](auto &&prop) { return read_property(std::get<0>(prop), std::get<1>(prop)); });
    for (auto &&property : view)
    {
        properties.emplace(std::move(property));
    }

    return properties;
}

} // namespace quite
