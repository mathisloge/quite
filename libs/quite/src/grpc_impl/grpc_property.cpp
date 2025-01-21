#include "grpc_property.hpp"
#include <quite/logger.hpp>
#include "grpc_value.hpp"
#include "probe_client.hpp"
#include "rpc/make_get_object_properties_request.hpp"

DEFINE_LOGGER(grpc_property_logger)

namespace quite::grpc_impl
{
GrpcProperty::GrpcProperty(ProbeServiceHandle probe_service,
                           std::shared_ptr<GrpcRemoteObject> parent,
                           std::string name,
                           const proto::Value &initial_value)
    : probe_service_{probe_service}
    , parent_{parent}
    , name_{std::move(name)}
    , last_value_{convert(initial_value, probe_service)}
    , type_id_{initial_value.type_id()}
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

const Result<Value> &GrpcProperty::value() const
{
    return last_value_;
}

AsyncResult<Value> GrpcProperty::read()
{
    LOG_DEBUG(grpc_property_logger, "get property[{}] for object={}", name_, parent_->id());

    // even though it is not really necessary to fetch the property here, it will get fetched, to verify that the
    // property exists.
    const auto properties = std::array{std::string{name_}};
    const auto response = co_await make_get_object_properties_request(
        probe_service_->context(), probe_service_->stub(), parent_->id(), properties);
    co_return response.and_then([&](auto &&reply) -> Result<Value> {
        auto it = reply.property_values().find(name_);
        if (it == reply.property_values().end())
        {
            return std::unexpected(Error{ErrorCode::not_found, "Server did not return the expected property."});
        }
        last_value_ = convert(it->second, probe_service_);
        return last_value_;
    });
}

AsyncResult<Value> GrpcProperty::write(const Value &value)
{
    co_return std::unexpected(Error{ErrorCode::unimplemented, "Client does not implement the write yet."});
}

} // namespace quite::grpc_impl
