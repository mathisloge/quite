#include "grpc_value.hpp"
#include "grpc_impl/grpc_remote_object.hpp"

namespace quite
{
#if 0
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
    if (type_info == entt::type_id<ArrayObject>())
    {
        return value.cast<ArrayObject>();
    }
    if (type_info == entt::type_id<MapObject>())
    {
        return value.cast<MapObject>();
    }
    if (type_info == entt::type_id<GenericClass>())
    {
        return value.cast<GenericClass>();
    }

    return make_error_result<quite::Value>(ErrorCode::invalid_argument,
                                           fmt::format("Could not convert value. Value name={}", type_info.name()));
}
#endif

void GrpcValueConverter::set_client(std::shared_ptr<proto::ProbeClient> client)
{
    client_ = std::move(client);
}

entt::meta_any GrpcValueConverter::from(ObjectReference ref) const
{
    return entt::forward_as_meta(std::make_shared<quite::GrpcRemoteObject>(std::move(ref), client_));
}
} // namespace quite
