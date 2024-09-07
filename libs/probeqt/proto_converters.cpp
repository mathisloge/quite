#include "proto_converters.hpp"
namespace quite::probe
{
entt::meta_any meta_from_value(const proto::Value &value)
{
    switch (value.value_oneof_case())
    {
    case proto::Value::kStringVal:
        return entt::meta_any{value.string_val()};
    case proto::Value::kIntVal:
        return entt::meta_any{value.int_val()};
    case proto::Value::kUintVal:
        return entt::meta_any{value.uint_val()};
    case proto::Value::kDoubleVal:
        return entt::meta_any{value.double_val()};
    case proto::Value::kBoolVal:
        return entt::meta_any{value.bool_val()};
    //! TODO: fill in these missing pieces
    case proto::Value::kClassVal:
    case proto::Value::kObjectVal:
    case proto::Value::kArrayVal:
    case proto::Value::VALUE_ONEOF_NOT_SET:
        break;
    }

    return entt::meta_any{};
}

} // namespace quite::probe
