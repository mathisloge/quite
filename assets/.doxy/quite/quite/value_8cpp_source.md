

# File value.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**value.cpp**](value_8cpp.md)

[Go to the documentation of this file](value_8cpp.md)


```C++
#include "value.hpp"
#include <ranges>
#include <entt/core/hashed_string.hpp>
#include <entt/meta/container.hpp>
#include <entt/meta/resolve.hpp>
#include <entt/meta/utility.hpp>
#include "quite/value/generic_value_class.hpp"
#include "quite/value/object_id.hpp"

using namespace entt::literals;

namespace quite::proto
{
namespace
{
void convert_class(const ValueRegistry &value_registry, Value &value, const entt::meta_any &any);
void convert_string(Value &value, const entt::meta_any &any);
void convert_arithmetic(Value &value, const entt::meta_any &any);
void convert_object_ptr(Value &value, const entt::meta_any &any);
void convert_sequence_container(const ValueRegistry &value_registry, Value &value, const entt::meta_any &any);
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
    else if (type.is_sequence_container())
    {
        convert_sequence_container(value_registry, value, any);
    }
    return value;
}

entt::meta_any convert_value(const ValueRegistry &value_registry, const IValueConverter &converter, const Value &value)
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
        return entt::forward_as_meta(value_registry.context(), std::string{value.string_val()});
    }
    if (value.has_object_val())
    {
        auto type_id = entt::resolve(value.type_id());
        if (type_id)
        {
            constexpr bool kDontTransferOwnership{false};
            return type_id.from_void(reinterpret_cast<void *>(value.object_val().object_id()), kDontTransferOwnership);
        }
        return converter.from(ObjectReference{.object_id = value.object_val().object_id(), .type_id = value.type_id()});
    }
    if (value.has_array_val())
    {
        std::vector<entt::meta_any> array;
        std::ranges::copy(std::views::transform(value.array_val().value(),
                                                [&value_registry, &converter](auto &&value) {
                                                    return convert_value(value_registry, converter, value);
                                                }),
                          std::back_inserter(array));
        return entt::forward_as_meta(std::move(array));
    }
    if (value.has_class_val())
    {
        GenericClass generic;
        for (auto &&member : value.class_val().value())
        {
            generic.properties.emplace(member.name(), convert_value(value_registry, converter, member.value()));
        }
        return entt::forward_as_meta(std::move(generic));
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

void convert_sequence_container(const ValueRegistry &value_registry, Value &value, const entt::meta_any &any)
{
    auto &&array = value.mutable_array_val();
    for (auto &&el : any.as_sequence_container())
    {
        *array->add_value() = create_value(value_registry, el);
    }
}
} // namespace
} // namespace quite::proto
```


