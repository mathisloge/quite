

# File meta\_types.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**meta**](dir_18a9029093157c789cf17586512ae04d.md) **>** [**meta\_types.hpp**](meta__types_8hpp.md)

[Go to the documentation of this file](meta__types_8hpp.md)


```C++
#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <fmt/core.h>
#include "meta_type_id.hpp"
#include "quite/quite_core_export.hpp"

namespace quite::meta
{
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
    std::vector<Property> properties;
    std::vector<Method> constructors;
    std::vector<Method> methods;
};
using ObjectTypePtr = std::unique_ptr<ObjectType>;

struct MapType
{
    TypeId id;
    std::string name;
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

    TypeId id;
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
```


