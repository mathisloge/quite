#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

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

struct MetaType
{
    std::string name;

    std::vector<Property> properties;
    std::vector<Method> signals;
    std::vector<Method> functions;
};

struct MapType
{
    TypeId key_type;
    TypeId value_type;
};

struct ListType
{
    TypeId value_type;
};

struct EnumType
{
    using ValueName = std::string;

    std::string name;
    std::unordered_map<ValueName, std::int64_t> values;
};

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

using Type = std::variant<PrimitiveType, ListType, MapType, std::unique_ptr<EnumType>, std::unique_ptr<MetaType>>;
} // namespace quite::meta
