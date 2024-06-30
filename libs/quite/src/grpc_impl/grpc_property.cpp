#include "grpc_property.hpp"
#include <quite/create_logger.hpp>
#include <quite/logger_macros.hpp>
#include <spdlog/spdlog.h>
#include "probe_client.hpp"
#include "rpc/make_get_object_properties_request.hpp"

namespace
{
LOGGER_IMPL(grpc_property)

quite::Value cnv_value(const quite::proto::Value &value, quite::grpc_impl::ProbeServiceHandle probe_service)
{
    if (value.has_bool_val())
    {
        return value.bool_val();
    }
    else if (value.has_int_val())
    {
        return value.int_val();
    }
    else if (value.has_double_val())
    {
        return value.double_val();
    }
    else if (value.has_string_val())
    {
        return value.string_val();
    }
    else if (value.has_object_val())
    {
        return std::make_shared<quite::grpc_impl::GrpcRemoteObject>(value.object_val().object_id(),
                                                                    std::move(probe_service));
    }
    else if (value.has_array_val())
    {
        SPDLOG_LOGGER_DEBUG(logger_grpc_property(), "array");
        quite::ArrayObject array{};
        array.values.reserve(value.array_val().value_size());
        for (auto &&val : value.array_val().value())
        {
            array.values.emplace_back(cnv_value(val, probe_service));
        }
        return xyz::indirect<quite::ArrayObject>(std::move(array));
    }
    return {};
}

} // namespace
namespace quite::grpc_impl
{
GrpcProperty::GrpcProperty(ProbeServiceHandle probe_service,
                           std::shared_ptr<GrpcRemoteObject> parent,
                           std::string name,
                           const proto::Value &initial_value)
    : probe_service_{probe_service}
    , parent_{parent}
    , name_{std::move(name)}
    , last_value_{cnv_value(initial_value, probe_service)}
{}

GrpcProperty::~GrpcProperty() = default;

const std::string &GrpcProperty::name() const noexcept
{
    return name_;
}

const Result<Value> &GrpcProperty::value() const noexcept
{
    return last_value_;
}

AsyncResult<Value> GrpcProperty::read() noexcept
{
    SPDLOG_LOGGER_DEBUG(logger_grpc_property(), "get property[{}] for object={}", name_, parent_->id());

    // even though it is not really necessary to fetch the property here, it will get fetch, to verify that the property
    // exists. Otherwise an unexpected event is returned.
    const std::vector<std::string_view> prop_vec{name_}; // workaround for gcc-13, (compiler crash when inlining this)
    const auto response = co_await make_get_object_properties_request(
        probe_service_->context(), probe_service_->stub(), parent_->id(), prop_vec);
    co_return response.and_then([&](auto &&reply) -> Result<Value> {
        auto it = reply.property_values().find(name_);
        if (it == reply.property_values().end())
        {
            return std::unexpected(Error{ErrorCode::not_found, "Server did not return the expected property."});
        }
        last_value_ = cnv_value(it->second, probe_service_);
        return last_value_;
    });
}

AsyncResult<Value> GrpcProperty::write(const Value &value) noexcept
{
    co_return std::unexpected(Error{ErrorCode::unimplemented, "Client does not implement the write yet."});
}

} // namespace quite::grpc_impl
