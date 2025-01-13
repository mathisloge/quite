#include "qt_meta_registry.hpp"
#include <QMetaMethod>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaType>
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

Result<meta::Type> convert(QMetaType type)
{
    const auto type_specifier = type.flags();
    type_specifier.testFlag(QMetaType::TypeFlag::IsEnumeration);
    type_specifier.testFlag(QMetaType::TypeFlag::IsGadget);
    type_specifier.testFlag(QMetaType::TypeFlag::PointerToGadget);
    type_specifier.testFlag(QMetaType::TypeFlag::PointerToQObject);

    QVariant meta_type_instance;
    if (type.flags().testFlag(QMetaType::TypeFlag::NeedsConstruction))
    {
        meta_type_instance = QVariant{type};
        if (type.metaObject() == nullptr)
        {
            return make_error_result<meta::Type>(
                ErrorCode::failed_precondition,
                fmt::format("Could not create an instance of '{}'. Type is default constructible ={}",
                            type.name(),
                            type.isDefaultConstructible()));
        }
    }

    const QMetaObject *meta_object = type.metaObject();
    if (meta_object != nullptr)
    {
        std::unique_ptr<meta::ObjectType> obj = std::make_unique<meta::ObjectType>();
        obj->name = meta_object->className();

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

        std::ranges::for_each(
            std::ranges::iota_view(0, meta_object->methodCount()) | std::views::transform([&](int prop_idx) {
                return meta_object->method(prop_idx);
            }) | std::views::transform(from_qmetamethod),
            [&obj](auto &&method) { obj->methods.emplace_back(std::forward<decltype(method)>(method)); });

        return meta::Type{std::move(obj)};
    }
    return make_error_result<meta::Type>(ErrorCode::failed_precondition, "Could not create a meta type from object");
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
