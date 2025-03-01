#include "grpc_value.hpp"
#include "grpc_impl/grpc_remote_object.hpp"

namespace quite
{
quite::Result<quite::Value> convert(const entt::meta_any &value, std::shared_ptr<proto::ProbeClient> client)
{
    const auto type = value.type();
    const auto type_info = type.info();
    if (type_info == entt::type_id<bool>())
    {
        return value.cast<bool>();
    }
    if (type.is_arithmetic() and type.is_integral())
    {
        if (type.is_signed())
        {
            return value.cast<std::int64_t>();
        }
        return value.cast<std::uint64_t>();
    }
    if (type.is_arithmetic())
    {
        return value.cast<double>();
    }
    if (type_info == entt::type_id<std::string>())
    {
        return value.cast<std::string>();
    }
    if (type_info == entt::type_id<ObjectReference>())
    {
        auto ref = value.cast<ObjectReference>();
        return std::make_shared<quite::GrpcRemoteObject>(ref, std::move(client));
    }
    // if (value.has_array_val())
    //{
    //    // quite::ArrayObject array{};
    //    // array.values.reserve(value.array_val().value_size());
    //    // for (auto &&val : value.array_val().value())
    //    // {
    //    //     // todo: propagate potential error up
    //    //     array.values.emplace_back(*convert(val, probe_service));
    //    // }
    //    // return xyz::indirect<quite::ArrayObject>(std::move(array));
    // }
    // if (value.has_class_val())
    //{
    //     quite::ClassObject class_obj{};
    //     class_obj.type_name = value.class_val().type_name();
    //     class_obj.members.reserve(value.class_val().value_size());
    //     for (auto &&val : value.class_val().value())
    //     {
    //         // todo: propagate potential error up
    //         class_obj.members.emplace_back(val.name(), *convert(val.value(), probe_service));
    //     }
    //     return xyz::indirect<quite::ClassObject>(std::move(class_obj));
    // }

    return make_error_result<quite::Value>(ErrorCode::invalid_argument,
                                           fmt::format("Could not convert value. Value name={}", type_info.name()));
}
} // namespace quite
