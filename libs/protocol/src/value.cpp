#include "quite/proto/value.hpp"
#include <entt/core/hashed_string.hpp>
#include <entt/meta/container.hpp>
#include <entt/meta/resolve.hpp>
#include <entt/meta/utility.hpp>
#include "quite/value/generic_value_class.hpp"

using namespace entt::literals;

namespace quite::proto
{
namespace
{
void convert_class(const ValueRegistry &value_registry, Value &value, const entt::meta_any &any);
void convert_string(Value &value, const entt::meta_any &any);
void convert_arithmetic(Value &value, const entt::meta_any &any);
void convert_object_ptr(Value &value, const entt::meta_any &any);
} // namespace

Value create_value(const ValueRegistry &value_registry, const entt::meta_any &any)
{
    Value value;
    const auto type = any.type();

    if (type.is_class() and not type.is_pointer_like())
    {
        const auto string_type = entt::resolve<std::string>();
        if (type.can_convert(string_type))
        {
            convert_string(value, any);
        }
        else
        {
            convert_class(value_registry, value, any);
        }
    }
    else if (type.is_arithmetic())
    {
        convert_arithmetic(value, any);
    }
    else if (type.is_pointer() or type.is_pointer_like())
    {
        convert_object_ptr(value, any);
    }
    return value;
}

entt::meta_any convert_value(const ValueRegistry &value_registry, const Value &value)
{
    if (value.has_bool_val())
    {
        return entt::forward_as_meta(value_registry.context(), value.bool_val());
    }
    if (value.has_int_val())
    {
        return entt::forward_as_meta(value_registry.context(), value.uint_val());
    }
    if (value.has_uint_val())
    {
        return entt::forward_as_meta(value_registry.context(), value.uint_val());
    }
    if (value.has_double_val())
    {
        return entt::forward_as_meta(value_registry.context(), value.double_val());
    }
    if (value.has_string_val())
    {
        return entt::forward_as_meta(value_registry.context(), value.string_val());
    }
    if (value.has_object_val())
    {
        auto type_id = entt::resolve(value.type_id());
        if (type_id)
        {
            constexpr bool kDontTransferOwnership{false};
            return type_id.from_void(reinterpret_cast<void *>(value.object_val().object_id()), kDontTransferOwnership);
        }
    }
    return entt::meta_any{};
}

namespace
{
void convert_class(const ValueRegistry &value_registry, Value &value, const entt::meta_any &any)
{
    const auto type = any.type();

    auto *class_value = value.mutable_class_val();
    if (type.info() == entt::type_id<GenericClass>())
    {
        const auto &properties = any.cast<GenericClass>().properties;
        for (auto &&[name, value] : properties)
        {
            auto &&class_member = class_value->add_value();
            class_member->set_name(name);
            *class_member->mutable_value() = create_value(value_registry, value);
        }
    }
    else
    {
        for (auto &&data_member : type.data())
        {
            auto it = value_registry.property_names().find(data_member.first);
            if (it == value_registry.property_names().end())
            {
                continue;
            }
            auto &&class_member = class_value->add_value();
            class_member->set_name(it->second);
            *class_member->mutable_value() = create_value(value_registry, data_member.second.get(any));
        }
    }
}

void convert_arithmetic(Value &value, const entt::meta_any &any)
{
    const auto type = any.type();
    if (type.info() == entt::type_id<bool>())
    {
        value.set_bool_val(any.cast<bool>());
    }
    else if (type.is_integral())
    {
        if (type.is_signed())
        {
            const auto casted_value = any.allow_cast<std::int64_t>();
            value.set_int_val(casted_value.cast<std::int64_t>());
        }
        else
        {
            const auto casted_value = any.allow_cast<std::uint64_t>();
            value.set_uint_val(casted_value.cast<std::uint64_t>());
        }
    }
    else
    {
        const auto casted_value = any.allow_cast<double>();
        value.set_double_val(casted_value.cast<double>());
    }
}

void convert_string(Value &value, const entt::meta_any &any)
{
    const auto string_any = any.allow_cast<std::string>();
    value.set_string_val(string_any.cast<std::string>());
}

void convert_object_ptr(Value &value, const entt::meta_any &any)
{
    const auto containing_value = *any;
    value.mutable_object_val()->set_object_id(reinterpret_cast<std::uint64_t>(containing_value.base().data()));
}
} // namespace
} // namespace quite::proto
