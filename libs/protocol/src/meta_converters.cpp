#include <ranges>
#include <quite/proto/meta_converters.hpp>

namespace quite::proto
{
namespace
{
meta::Method transform_method(const MetaMethod &method)
{
    auto m = meta::Method{.name = method.name(), .return_type = method.return_type_id()};
    std::ranges::copy(method.parameter_types() | std::views::transform([](auto &&name_type_id_pair) {
                          return meta::Property{.name = name_type_id_pair.first, .type = name_type_id_pair.second};
                      }),
                      std::back_inserter(m.parameters));
    return m;
}
} // namespace

meta::PrimitiveType from_protocol(const MetaPrimitiveType &type)
{
    switch (type)
    {
    case MetaPrimitiveType::unknown:
        return meta::PrimitiveType::type_unknown;
    case MetaPrimitiveType::void_:
        return meta::PrimitiveType::type_void;
    case MetaPrimitiveType::int_:
        return meta::PrimitiveType::type_int;
    case MetaPrimitiveType::uint:
        return meta::PrimitiveType::type_uint;
    case MetaPrimitiveType::float_:
        return meta::PrimitiveType::type_float;
    case MetaPrimitiveType::double_:
        return meta::PrimitiveType::type_double;
    case MetaPrimitiveType::bool_:
        return meta::PrimitiveType::type_bool;
    case MetaPrimitiveType::string:
        return meta::PrimitiveType::type_string;
    case MetaPrimitiveType::MetaPrimitiveType_INT_MIN_SENTINEL_DO_NOT_USE_:
    case MetaPrimitiveType::MetaPrimitiveType_INT_MAX_SENTINEL_DO_NOT_USE_:
        break;
    }
    return meta::PrimitiveType::type_unknown;
}

meta::ListType from_protocol(const MetaListType &type)
{
    return meta::ListType{.id = type.type_id(), .name = type.name(), .value_type = type.value_type_id()};
}

meta::MapType from_protocol(const MetaMapType &type)
{
    return meta::MapType{
        .id = type.type_id(), .name = type.name(), .key_type = type.key_type_id(), .value_type = type.value_type_id()};
}

meta::ObjectTypePtr from_protocol(const MetaObjectType &type)
{
    auto obj = std::make_unique<meta::ObjectType>();
    obj->id = type.type_id();
    obj->name = type.name();
    std::ranges::copy(type.properties() | std::views::transform([](auto &&meta_prop) {
                          return meta::Property{.name = meta_prop.name(), .type = meta_prop.type_id()};
                      }),
                      std::back_inserter(obj->properties));

    std::ranges::copy(type.constructors() | std::views::transform(transform_method),
                      std::back_inserter(obj->constructors));

    std::ranges::copy(type.methods() | std::views::transform(transform_method), std::back_inserter(obj->methods));

    return obj;
}

meta::EnumTypePtr from_protocol(const MetaEnumType &type)
{
    auto meta_enum = std::make_unique<meta::EnumType>();
    meta_enum->id = type.type_id();
    meta_enum->name = type.name();
    for (auto &&[name, value] : type.name_value())
    {
        meta_enum->values.emplace(name, value);
    }
    return meta_enum;
}

struct ProtocolVisitor
{
    MetaType &proto;

    void operator()(const meta::PrimitiveType &meta)
    {
        switch (meta)
        {
        case meta::PrimitiveType::type_unknown:
            proto.set_primitive_type(MetaPrimitiveType::unknown);
            break;
        case meta::PrimitiveType::type_void:
            proto.set_primitive_type(MetaPrimitiveType::void_);
            break;
        case meta::PrimitiveType::type_int:
            proto.set_primitive_type(MetaPrimitiveType::int_);
            break;
        case meta::PrimitiveType::type_uint:
            proto.set_primitive_type(MetaPrimitiveType::uint);
            break;
        case meta::PrimitiveType::type_float:
            proto.set_primitive_type(MetaPrimitiveType::float_);
            break;
        case meta::PrimitiveType::type_double:
            proto.set_primitive_type(MetaPrimitiveType::double_);
            break;
        case meta::PrimitiveType::type_bool:
            proto.set_primitive_type(MetaPrimitiveType::bool_);
            break;
        case meta::PrimitiveType::type_string:
            proto.set_primitive_type(MetaPrimitiveType::string);
            break;
        }
    }

    void operator()(const meta::ListType &meta)
    {
        auto &&list = proto.mutable_list_type();
        list->set_type_id(meta.id);
        list->set_value_type_id(meta.value_type);
        list->set_name(meta.name);
    }

    void operator()(const meta::MapType &meta)
    {
        auto &&map = proto.mutable_map_type();
        map->set_name(meta.name);
        map->set_type_id(meta.id);
        map->set_key_type_id(meta.key_type);
        map->set_value_type_id(meta.value_type);
    }

    void operator()(const meta::EnumTypePtr &meta)
    {
        auto &&enum_entry = proto.mutable_enum_type();
        enum_entry->set_name(meta->name);
        enum_entry->set_type_id(meta->id);
        for (auto &&[name, value] : meta->values)
        {
            enum_entry->mutable_name_value()->insert({name, static_cast<std::uint64_t>(value)});
        }
    }

    void operator()(const meta::ObjectTypePtr &meta)
    {
        auto &&object = proto.mutable_object_type();
        object->set_type_id(meta->id);
        object->set_name(meta->name);
        for (auto &&x : meta->properties)
        {
            object->add_properties()->set_name(x.name);
        }
        std::ranges::for_each(
            meta->properties,
            [](auto &&property_pack) {
                auto &&[proto, meta] = property_pack;
                proto->set_name(meta.name);
                proto->set_type_id(meta.type);
            },
            [&object](auto &&prop) { return std::tuple{object->add_properties(), prop}; });

        auto add_method = [](std::tuple<MetaMethod *, const meta::Method &> method_meta_pack) {
            auto &&[method, meta] = method_meta_pack;
            method->set_name(meta.name);
            method->set_return_type_id(meta.return_type);
            std::ranges::for_each(
                meta.parameters,
                [&method](auto &&param) { method->mutable_parameter_types()->insert({param.name, param.type}); },
                [](auto &&property) { return property; });
        };

        std::ranges::for_each(meta->methods, add_method, [&object](auto &&method) {
            return std::tuple<MetaMethod *, const meta::Method &>{object->add_methods(), method};
        });

        std::ranges::for_each(meta->constructors, add_method, [&object](auto &&method) {
            return std::tuple<MetaMethod *, const meta::Method &>{object->add_constructors(), method};
        });
    }
};

void to_protocol(const meta::Type &type, MetaType &proto)
{
    std::visit(ProtocolVisitor{proto}, type);
}
} // namespace quite::proto
