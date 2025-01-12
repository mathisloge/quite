#include "qt_meta_registry.hpp"
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

        std::ranges::for_each(
            std::ranges::iota_view(0, meta_object->propertyCount()) | std::views::transform([&](int prop_idx) {
                return meta_object->property(prop_idx);
            }) | std::views::transform([&](auto &&prop) {
                return meta::Property{.name = prop.name(), .type = static_cast<meta::TypeId>(prop.typeId())};
            }),
            [&obj](auto &&property) { obj->properties.emplace_back(std::forward<decltype(property)>(property)); });
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
