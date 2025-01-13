#include "quite/meta/meta_types.hpp"
#include <utility>
#include <fmt/ranges.h>

namespace
{
struct FormatVisitor
{
    template <typename T>
    auto operator()(const std::unique_ptr<T> &type)
    {
        return fmt::format("{}", *type);
    }

    auto operator()(auto &&type)
    {
        return fmt::format("{}", type);
    }
};
} // namespace

auto fmt::formatter<quite::meta::Property>::format(const quite::meta::Property &type, format_context &ctx) const
    -> format_context::iterator
{
    return fmt::format_to(ctx.out(), "Property(name={}, type_id={})", type.name, type.type);
}

auto fmt::formatter<quite::meta::Method>::format(const quite::meta::Method &type, format_context &ctx) const
    -> format_context::iterator
{
    return fmt::format_to(
        ctx.out(), "Method(name={}, returns={}, parameters={})", type.name, type.return_type, type.parameters);
}

auto fmt::formatter<quite::meta::ObjectType>::format(const quite::meta::ObjectType &type, format_context &ctx) const
    -> format_context::iterator
{
    return fmt::format_to(ctx.out(),
                          "ObjectType(name={}, superclass={}, properties={}, constructors={}, methods={})",
                          type.name,
                          type.superclass.has_value() ? fmt::format("{}", type.superclass.value()) : "None",
                          type.properties,
                          type.constructors,
                          type.methods);
}

auto fmt::formatter<quite::meta::MapType>::format(const quite::meta::MapType &type, format_context &ctx) const
    -> format_context::iterator
{
    return fmt::format_to(ctx.out(), "MapType(key={}, value={})", type.key_type, type.value_type);
}

auto fmt::formatter<quite::meta::ListType>::format(const quite::meta::ListType &type, format_context &ctx) const
    -> format_context::iterator
{
    return fmt::format_to(ctx.out(), "ListType(type_id={})", type.value_type);
}

auto fmt::formatter<quite::meta::EnumType>::format(const quite::meta::EnumType &type, format_context &ctx) const
    -> format_context::iterator
{
    return fmt::format_to(ctx.out(), "EnumType(name={}, values={})", type.name, type.values);
}

auto fmt::formatter<quite::meta::PrimitiveType>::format(const quite::meta::PrimitiveType &type,
                                                        format_context &ctx) const -> format_context::iterator
{
    return fmt::format_to(ctx.out(), "PrimitiveType::{}", std::to_underlying(type));
}

auto fmt::formatter<quite::meta::Type>::format(const quite::meta::Type &type, format_context &ctx) const
    -> format_context::iterator
{
    return fmt::format_to(ctx.out(), "Type({})", std::visit(FormatVisitor{}, type));
}
