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
} // namespace

Value create_value(const ValueRegistry &value_registry, const entt::meta_any &any)
{
    Value value;
    const auto type = any.type();

    if (type.is_class())
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
    return value;
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
} // namespace
} // namespace quite::proto
