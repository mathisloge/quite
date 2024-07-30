#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace quite
{

using TypeId = std::int64_t; // is mirroring probes type id numbers

enum class PrimitveType
{
    unknown = 0,
    t_int,
    t_float,
    t_double,
    t_bool,
    t_string
};

struct EnumType
{
    TypeId enum_type;
};

struct ListType
{
    TypeId element_types;
};

struct MapType
{
    TypeId key_type;
    TypeId value_type;
};

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

class MetaObject
{

  private:
    std::string type_name_;
    std::vector<Property> properties_;
    std::vector<Method> signals_;
    std::vector<Method> slots_;
};
} // namespace quite
