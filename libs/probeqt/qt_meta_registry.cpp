#include "qt_meta_registry.hpp"
#include <QAssociativeIterable>
#include <QMetaMethod>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaType>
#include <QSequentialIterable>
#include <ranges>
#include <entt/meta/resolve.hpp>
#include <quite/logger.hpp>

DEFINE_LOGGER(qt_meta_registry);

namespace quite::probe
{
namespace
{
constexpr meta::Property from_qmetaproperty(const QMetaProperty &prop)
{
    return meta::Property{.name = prop.name(), .type = static_cast<meta::TypeId>(prop.typeId())};
}

auto from_qmetamethod(const QMetaMethod &method)
{
    meta::Method meta_method{.name = method.methodSignature().toStdString(),
                             .return_type = static_cast<meta::TypeId>(method.returnType())};
    std::ranges::for_each(std::ranges::iota_view(0, method.parameterCount()) | std::views::transform([&](int prop_idx) {
                              return meta::Property{.name = method.parameterNames().at(prop_idx).toStdString(),
                                                    .type = static_cast<meta::TypeId>(method.parameterType(prop_idx))};
                          }),
                          [&meta_method](auto &&property) {
                              meta_method.parameters.emplace_back(std::forward<decltype(property)>(property));
                          });
    return meta_method;
}

Result<meta::Type> convert_enum_type(QMetaType type)
{
    LOG_DEBUG(qt_meta_registry, "Converting to enum. Name {}", type.name());
    auto meta_enum = std::make_unique<meta::EnumType>();
    meta_enum->name = type.name();
    const QMetaObject *meta_object = type.metaObject();
    if (type.metaObject() == nullptr)
    {
        return make_error_result<meta::Type>(ErrorCode::failed_precondition,
                                             fmt::format("Could not get a QMetaObject from '{}'", type.name()));
    }

    // the indexOfEnumerator function expect the simple name, but the type.name() always returns the fully qualified
    // name
    const std::string_view qualified_enum_name = type.name();
    std::string_view simple_enum_name = qualified_enum_name;
    const auto ns_end_pos = qualified_enum_name.find_last_of(':');
    if (ns_end_pos != std::string_view::npos)
    {
        simple_enum_name = qualified_enum_name.substr(ns_end_pos + 1);
    }
    const auto enum_idx = meta_object->indexOfEnumerator(simple_enum_name.begin());
    if (enum_idx < 0)
    {
        return make_error_result<meta::Type>(
            ErrorCode::failed_precondition,
            fmt::format("Could not find enum index of type '{}' in enclosing type '{}'",
                        type.name(),
                        meta_object->className()));
    }
    const auto qt_meta_enum = meta_object->enumerator(enum_idx);

    std::ranges::for_each(
        std::ranges::iota_view(0, qt_meta_enum.keyCount()) | std::views::transform([&](int index) {
            return std::make_pair<meta::EnumType::ValueName, std::int64_t>(qt_meta_enum.key(index),
                                                                           qt_meta_enum.value(index));
        }),
        [&meta_enum](auto &&enum_value) { meta_enum->values.emplace(std::forward<decltype(enum_value)>(enum_value)); });

    return meta_enum;
}

Result<meta::Type> convert_list_type(QMetaType list_type, QMetaType containing_type)
{
    LOG_DEBUG(qt_meta_registry, "List type '{}' with containing type '{}'", list_type.name(), containing_type.name());

    return meta::ListType{.id = static_cast<meta::TypeId>(list_type.id()),
                          .name = list_type.name(),
                          .value_type = static_cast<meta::TypeId>(containing_type.id())};
}

Result<meta::Type> convert_map_type(QMetaType map_type, QMetaType key_type, QMetaType value_type)
{
    LOG_DEBUG(qt_meta_registry, "Map type: {} k: {} v: {}", map_type.name(), key_type.name(), value_type.name());

    return meta::MapType{.name = map_type.name(),
                         .id = static_cast<meta::TypeId>(map_type.id()),
                         .key_type = static_cast<meta::TypeId>(key_type.id()),
                         .value_type = static_cast<meta::TypeId>(value_type.id())};
}

Result<meta::Type> convert_object_type(QMetaType type)
{
    QVariant meta_type_instance;
    if (type.flags().testFlag(QMetaType::TypeFlag::NeedsConstruction))
    {
        meta_type_instance = QVariant{type};
        if (type.metaObject() == nullptr)
        {
            // TODO convert to either list or map types
            if (meta_type_instance.canConvert<QVariantList>())
            {
                const auto iterable = meta_type_instance.value<QSequentialIterable>();
                return convert_list_type(type, iterable.metaContainer().valueMetaType());
            }
            if (meta_type_instance.canConvert<QVariantMap>())
            {
                const auto iterable = meta_type_instance.value<QAssociativeIterable>();
                return convert_map_type(
                    type, iterable.metaContainer().keyMetaType(), iterable.metaContainer().mappedMetaType());
            }
            return make_error_result<meta::Type>(
                ErrorCode::failed_precondition,
                fmt::format("Could not create an instance of '{}'. Type is default constructible ={}",
                            type.name(),
                            type.isDefaultConstructible()));
        }
    }

    const QMetaObject *meta_object = type.metaObject();
    if (meta_object == nullptr)
    {
        return make_error_result<meta::Type>(ErrorCode::failed_precondition,
                                             "Could not create a meta type from object");
    }
    std::unique_ptr<meta::ObjectType> obj = std::make_unique<meta::ObjectType>();
    obj->name = meta_object->className();
    obj->id = type.id();

    if (meta_object->superClass() != nullptr)
    {
        obj->superclass = meta_object->superClass()->metaType().id();
    }

    std::ranges::for_each(
        std::ranges::iota_view(0, meta_object->propertyCount()) | std::views::transform([&](int prop_idx) {
            return meta_object->property(prop_idx);
        }) | std::views::transform(from_qmetaproperty),
        [&obj](auto &&property) { obj->properties.emplace_back(std::forward<decltype(property)>(property)); });

    std::ranges::for_each(
        std::ranges::iota_view(0, meta_object->constructorCount()) | std::views::transform([&](int prop_idx) {
            return meta_object->constructor(prop_idx);
        }) | std::views::transform(from_qmetamethod),
        [&obj](auto &&method) { obj->constructors.emplace_back(std::forward<decltype(method)>(method)); });

    std::ranges::for_each(std::ranges::iota_view(0, meta_object->methodCount()) |
                              std::views::transform([&](int prop_idx) { return meta_object->method(prop_idx); }) |
                              std::views::transform(from_qmetamethod),
                          [&obj](auto &&method) { obj->methods.emplace_back(std::forward<decltype(method)>(method)); });

    return meta::Type{std::move(obj)};
}

Result<meta::Type> convert(QMetaType type)
{
    if (type.flags().testFlag(QMetaType::TypeFlag::IsEnumeration))
    {
        return convert_enum_type(type);
    }
    return convert_object_type(type);
}
} // namespace

AsyncResult<meta::Type> QtMetaRegistry::lookup_type(meta::TypeId type_id)
{
    auto qt_meta_result = QMetaType{static_cast<int>(type_id)};
    if (qt_meta_result.isValid())
    {
        co_return convert(qt_meta_result);
    }

    auto internal_result = entt::resolve(type_id);
    if (internal_result)
    {
    }

    co_return make_error_result<meta::Type>(ErrorCode::not_found,
                                            fmt::format("Could not find type with id '{}'", type_id));
}
} // namespace quite::probe
