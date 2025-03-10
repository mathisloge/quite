#include "grpc_property.hpp"
#include <quite/logger.hpp>

DEFINE_LOGGER(grpc_property_logger)

namespace quite::client
{
GrpcProperty::GrpcProperty(std::shared_ptr<GrpcRemoteObject> parent, std::string name, entt::meta_any initial_value)
    : parent_{std::move(parent)}
    , name_{std::move(name)}
    , last_value_{std::move(initial_value)}
    , type_id_{0} // TODO
{}

GrpcProperty::~GrpcProperty() = default;

const std::string &GrpcProperty::name() const
{
    return name_;
}

meta::TypeId GrpcProperty::type_id() const
{
    return type_id_;
}

const Result<entt::meta_any> &GrpcProperty::value() const
{
    return last_value_;
}

AsyncResult<entt::meta_any> GrpcProperty::read()
{
    LOG_DEBUG(grpc_property_logger(), "get property[{}] for object={}", name_, parent_->id());
    last_value_ = co_await parent_->fetch_property({name_});
    co_return last_value_;
}

AsyncResult<entt::meta_any> GrpcProperty::write(entt::meta_any value)
{
    co_return std::unexpected(Error{ErrorCode::unimplemented, "Client does not implement the write yet."});
}

} // namespace quite::client
