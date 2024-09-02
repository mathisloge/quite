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

class MetaType
{
    std::string type_name_;

    std::vector<Property> properties_;
    std::vector<Method> signals_;
    std::vector<Method> functions_;
};

class MapType
{
    TypeId key_type_;
    TypeId value_type_;
};

class ListType
{
    TypeId element_type_;
};

class EnumType
{
    using ValueName = std::string;

    std::string type_name_;
    std::unordered_map<ValueName, std::int64_t> values_;
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
