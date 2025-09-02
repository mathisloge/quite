// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "property_collector.hpp"
#include <QMetaProperty>
#include <QQmlListReference>
#include <ranges>
#include <entt/meta/factory.hpp>
#include <quite/logger.hpp>
#include <quite/meta_any_formatter.hpp>
#include <quite/value/generic_value_class.hpp>
#include "qt_meta_type_accessor.hpp"
#include "quite/value/object_id.hpp"
#include "to_object_id.hpp"

using namespace entt::literals;

DEFINE_LOGGER(property_collector_logger)
namespace quite
{
ObjectMeta ObjectMeta::from_qobject(QObject *object)
{
    return ObjectMeta{.object = object, .meta_object = probe::try_get_qt_meta_object(object)};
}

entt::meta_any convert_void_ptr_to_any(QMetaType meta_type, const void *data_ptr)
{
    entt::meta_any value;

    // important: check for explicit conversions first. E.g. QQuickAnchorLine is a QGadget but should be converted with
    // the explicit converter.
    if (auto custom_meta_type = entt::resolve(entt::hashed_string{meta_type.name()}.value()); custom_meta_type)
    {
        LOG_DEBUG(
            property_collector_logger(), "got known type {} for {}", custom_meta_type.info().name(), meta_type.name());
        // create a copy of the underlying variant object and transfer the ownership.
        value = custom_meta_type.from_void(meta_type.create(data_ptr), true);
    }
    else if (meta_type.flags().testFlag(QMetaType::PointerToQObject))
    {
        const QObject *obj = *reinterpret_cast<QObject *const *>(data_ptr);

        return ObjectReference{
            .object_id = probe::to_object_id(obj),
            .type_id = static_cast<meta::TypeId>(probe::try_get_qt_meta_type(obj).id()),
        };
    }
    else if (meta_type.flags().testAnyFlags(QMetaType::IsGadget | QMetaType::PointerToGadget))
    {
        auto &&gadget_metaobj = meta_type.metaObject();
        LOG_DEBUG(property_collector_logger(),
                  "raw-value '{}' convertible to QGadget (props={})",
                  meta_type.name(),
                  gadget_metaobj->propertyCount());
        GenericClass generic_class;
        auto view =
            std::ranges::iota_view(0, gadget_metaobj->propertyCount()) |
            std::views::transform([&](int prop_idx) { return gadget_metaobj->property(prop_idx); }) |
            std::views::filter([](const QMetaProperty &prop) { return prop.isValid() and prop.isReadable(); }) |
            std::views::transform([&](auto &&prop) {
                return std::tuple{prop.readOnGadget(data_ptr), std::forward<decltype(prop)>(prop)};
            }) |
            std::views::transform([&](auto &&prop) { return read_property(std::get<0>(prop), std::get<1>(prop)); });
        for (auto &&name_value : view)
        {
            generic_class.properties.emplace(std::forward<decltype(name_value)>(name_value));
        }
        value = std::move(generic_class);
    }
    else if (meta_type.flags().testFlag(QMetaType::IsEnumeration))
    {
        entt::hashed_string data_type =
            meta_type.flags().testFlag(QMetaType::IsUnsignedEnumeration) ? "qulonglong"_hs : "qlonglong"_hs;
        LOG_DEBUG(property_collector_logger(), "raw-value '{}' convertible to {}", meta_type.name(), data_type.value());
        auto custom_meta_type = entt::resolve(data_type.value());
        value = value = custom_meta_type.from_void(meta_type.create(data_ptr), true);
    }
#if (QT_VERSION >= QT_VERSION_CHECK(6, 7, 0))
    else if (QQmlListReference qml_list{QVariant::fromMetaType(meta_type, data_ptr)};
             qml_list.isValid() and qml_list.canCount() and qml_list.canAt())
    {
        LOG_DEBUG(property_collector_logger(), "raw-value '{}' convertible to QQmlListReference", meta_type.name());
        const auto size = qml_list.count();
        std::vector<entt::meta_any> object_list;
        object_list.reserve(size);
        for (qsizetype i = 0; i < size; i++)
        {
            object_list.emplace_back(entt::forward_as_meta(qml_list.at(i)));
        }
        value = std::move(object_list);
    }
#endif
    else
    {
        LOG_DEBUG(property_collector_logger(), "raw-value '{}' not convertible", meta_type.name());
    }
    return value;
}

std::pair<std::string, entt::meta_any> read_property(const QVariant property_value, const QMetaProperty &property)
{
    return {property.name(), convert_void_ptr_to_any(property.metaType(), property_value.data())};
}

Result<void> write_property(const ObjectMeta &meta,
                            const std::string &property_name,
                            const entt::meta_any &property_value)
{
    const auto idx = meta.meta_object->indexOfProperty(property_name.c_str());
    const auto prop = meta.meta_object->property(idx);

    if (not prop.isValid())
    {
        return make_error_result(ErrorCode::failed_precondition,
                                 fmt::format("Property {} is not valid", property_name));
    }

    if (not prop.isWritable())
    {
        return make_error_result(ErrorCode::failed_precondition,
                                 fmt::format("Property {} is not writable", property_name));
    }

    auto &&variant_value = property_value.allow_cast<QVariant>();
    if (not variant_value)
    {
        return make_error_result(ErrorCode::failed_precondition,
                                 fmt::format("Could not convert {} to QVariant", property_value));
    }

    const auto written = prop.write(meta.object, variant_value.cast<QVariant>());

    if (not written)
    {
        return make_error_result(ErrorCode::aborted,
                                 fmt::format("Could not write {} to {}", property_value, property_name));
    }
    return {};
}

entt::dense_map<std::string, entt::meta_any> collect_properties(ObjectMeta object_meta,
                                                                std::span<const std::string> property_names)
{
    entt::dense_map<std::string, entt::meta_any> properties;

    auto view = std::ranges::iota_view(0, object_meta.meta_object->propertyCount()) | //
                std::views::transform([&](int prop_idx) { return object_meta.meta_object->property(prop_idx); }) |
                std::views::filter([](auto &&prop) { return prop.isValid() and prop.isReadable(); }) |
                std::views::filter([&property_names](auto &&prop) {
                    if (property_names.size() == 0)
                    {
                        return true;
                    }
                    const auto it = std::ranges::find(property_names, prop.name());
                    return it != property_names.end();
                }) |
                std::views::transform([&](auto &&prop) {
                    return std::tuple{prop.read(object_meta.object), std::forward<decltype(prop)>(prop)};
                }) |
                std::views::transform([&](auto &&prop) { return read_property(std::get<0>(prop), std::get<1>(prop)); });
    for (auto &&property : view)
    {
        properties.emplace(std::forward<decltype(property)>(property));
    }

    return properties;
}

} // namespace quite
