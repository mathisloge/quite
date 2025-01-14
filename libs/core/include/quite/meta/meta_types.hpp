#pragma once
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <fmt/core.h>
#include "quite_core_export.h"

namespace quite::meta
{

using TypeId = std::uint64_t;

struct Property
{
    std::string name;
    TypeId type;
};

struct Method
{
    std::string name;
    TypeId return_type;
    std::vector<Property> parameters;
};

struct ObjectType
{
    TypeId id;
    std::string name;
    std::optional<TypeId> superclass;
    std::vector<Property> properties;
    std::vector<Method> constructors;
    std::vector<Method> methods;
};
using ObjectTypePtr = std::unique_ptr<ObjectType>;

struct MapType
{
    TypeId key_type;
    TypeId value_type;
};

struct ListType
{
    TypeId id;
    std::string name;
    TypeId value_type;
};

struct EnumType
{
    using ValueName = std::string;

    std::string name;
    std::unordered_map<ValueName, std::int64_t> values;
};
using EnumTypePtr = std::unique_ptr<EnumType>;

enum class PrimitiveType
{
    type_unknown = 0,
    type_void,
    type_int,
    type_uint,
    type_float,
    type_double,
    type_bool,
    type_string
};

using Type = std::variant<PrimitiveType, ListType, MapType, EnumTypePtr, ObjectTypePtr>;
} // namespace quite::meta

template <>
struct QUITE_CORE_EXPORT fmt::formatter<quite::meta::Property> : fmt::formatter<std::string_view>
{
    auto format(const quite::meta::Property &type, format_context &ctx) const -> format_context::iterator;
};

template <>
struct QUITE_CORE_EXPORT fmt::formatter<quite::meta::Method> : fmt::formatter<std::string_view>
{
    auto format(const quite::meta::Method &type, format_context &ctx) const -> format_context::iterator;
};

template <>
struct QUITE_CORE_EXPORT fmt::formatter<quite::meta::ObjectType> : fmt::formatter<std::string_view>
{
    auto format(const quite::meta::ObjectType &type, format_context &ctx) const -> format_context::iterator;
};

template <>
struct QUITE_CORE_EXPORT fmt::formatter<quite::meta::MapType> : fmt::formatter<std::string_view>
{
    auto format(const quite::meta::MapType &type, format_context &ctx) const -> format_context::iterator;
};

template <>
struct QUITE_CORE_EXPORT fmt::formatter<quite::meta::ListType> : fmt::formatter<std::string_view>
{
    auto format(const quite::meta::ListType &type, format_context &ctx) const -> format_context::iterator;
};

template <>
struct QUITE_CORE_EXPORT fmt::formatter<quite::meta::EnumType> : fmt::formatter<std::string_view>
{
    auto format(const quite::meta::EnumType &type, format_context &ctx) const -> format_context::iterator;
};

template <>
struct QUITE_CORE_EXPORT fmt::formatter<quite::meta::PrimitiveType> : fmt::formatter<std::string_view>
{
    auto format(const quite::meta::PrimitiveType &type, format_context &ctx) const -> format_context::iterator;
};

template <>
struct QUITE_CORE_EXPORT fmt::formatter<quite::meta::Type> : fmt::formatter<std::string_view>
{
    auto format(const quite::meta::Type &type, format_context &ctx) const -> format_context::iterator;
};
