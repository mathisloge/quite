#include <quite/proto/meta_converters.hpp>

namespace quite::proto
{
meta::PrimitiveType from_protocol(const MetaPrimitiveType &type)
{
    switch (type)
    {
    case unknown:
        return meta::PrimitiveType::type_unknown;
    case void_:
        return meta::PrimitiveType::type_void;
    case int_:
        return meta::PrimitiveType::type_int;
    case float_:
        return meta::PrimitiveType::type_float;
    case double_:
        return meta::PrimitiveType::type_double;
    case bool_:
        return meta::PrimitiveType::type_bool;
    case string:
        return meta::PrimitiveType::type_string;
    case MetaPrimitiveType_INT_MIN_SENTINEL_DO_NOT_USE_:
    case MetaPrimitiveType_INT_MAX_SENTINEL_DO_NOT_USE_:
        break;
    }
    return meta::PrimitiveType::type_unknown;
}

meta::ListType from_protocol(const MetaListType &type)
{}

meta::MapType from_protocol(const MetaMapType &type)
{}

meta::ObjectType from_protocol(const MetaObjectType &type)
{}

void to_protocol(const meta::Type &type, MetaType &proto)
{}
} // namespace quite::proto
