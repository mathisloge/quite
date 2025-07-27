// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "probe_service_impl.hpp"
#include <quite/logger.hpp>
#include "configure_client_context.hpp"
#include "error_helper.hpp"
#include "value.hpp"

DEFINE_LOGGER(grpc_probe)

namespace quite::proto
{
namespace
{
void write_query(proto::ObjectSearchQuery &proto_query, const ObjectQuery &query)
{
    if (query.container != nullptr)
    {
        write_query(*proto_query.mutable_parent(), *query.container);
    }
    proto_query.set_type_name(query.type_name);
    for (auto &&[key, value] : query.properties)
    {
        proto_query.mutable_properties()->insert({key, create_value(entt::locator<ValueRegistry>::value(), value)});
    }
}
} // namespace

ProbeServiceImpl::ProbeServiceImpl(std::shared_ptr<agrpc::GrpcContext> grpc_context,
                                   ProbeService::Stub &probe_service_stub,
                                   std::shared_ptr<IValueConverter> value_converter)
    : grpc_context_{std::move(grpc_context)}
    , probe_service_stub_{probe_service_stub}
    , value_converter_{std::move(value_converter)}
{}

AsyncResult<Image> ProbeServiceImpl::take_snapshot(ObjectId id)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncCreateScreenshot>;
    grpc::ClientContext client_context;
    configure_client_context(client_context);

    RPC::Request request;
    request.set_object_id(id);
    RPC rpc{*grpc_context_};

    co_await rpc.start(probe_service_stub_, request, agrpc::use_sender);

    bool do_read{true};
    quite::proto::ImageMetadata meta_data;
    std::vector<std::byte> image_data;
    while (do_read)
    {
        RPC::Response response;
        do_read = co_await rpc.read(response, agrpc::use_sender);
        const auto data_size = response.data().size();
        LOG_DEBUG(grpc_probe(), "got snapshot chunk. Size={}. Has more to read={}", data_size, do_read);
        const auto data_view = std::as_bytes(std::span{response.data().data(), data_size});
        std::copy(data_view.begin(), data_view.end(), std::back_inserter(image_data));
        if (response.has_metadata())
        {
            meta_data = response.metadata();
        }
    }
    const auto status = co_await rpc.finish(agrpc::use_sender);
    LOG_DEBUG(grpc_probe(), "snapshot finished with status={}", status.ok());
    if (not status.ok())
    {
        co_return std::unexpected(grpc_status2result(status));
    }
    LOG_DEBUG(grpc_probe(), "got final snapshot. Size={}", image_data.size());
    co_return Image{std::move(image_data), meta_data.width(), meta_data.height(), 4};
}

AsyncResult<ObjectReference> ProbeServiceImpl::find_object(ObjectQuery serach_query)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncFindObject>;
    grpc::ClientContext client_context;
    configure_client_context(client_context);

    RPC::Request request;
    auto &&proto_query = request.mutable_query();

    write_query(*proto_query, serach_query);

    RPC::Response response;
    const auto status = co_await RPC::request(*grpc_context_, probe_service_stub_, client_context, request, response);
    if (not status.ok())
    {
        co_return std::unexpected(grpc_status2result(status));
    }
    co_return ObjectReference{.object_id = response.object_id(), .type_id = response.type_id()};
}

AsyncResult<std::unordered_map<std::string, entt::meta_any>> ProbeServiceImpl::get_object_properties(
    ObjectId object_id, std::vector<std::string> properties)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncGetObjectProperties>;
    grpc::ClientContext client_context;
    configure_client_context(client_context);

    RPC::Request request;
    request.set_object_id(object_id);
    request.mutable_property_names()->Reserve(static_cast<int>(properties.size()));
    for (auto property_name : properties)
    {
        request.mutable_property_names()->Add(std::string{property_name});
    }

    RPC::Response response;
    const auto status = co_await RPC::request(*grpc_context_, probe_service_stub_, client_context, request, response);
    if (not status.ok())
    {
        co_return std::unexpected{grpc_status2result(status)};
    }

    std::unordered_map<std::string, entt::meta_any> responses;
    for (auto &&[k, v] : response.property_values())
    {
        responses.emplace(k, convert_value(entt::locator<ValueRegistry>::value(), *value_converter_, v));
    }
    co_return responses;
}

AsyncResult<void> ProbeServiceImpl::set_object_property(ObjectId object_id, std::string property, entt::meta_any value)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncSetObjectProperty>;
    grpc::ClientContext client_context;
    configure_client_context(client_context);

    RPC::Request request;
    request.set_object_id(object_id);
    request.set_property(std::move(property));
    *request.mutable_value() = create_value(entt::locator<ValueRegistry>::value(), value);

    RPC::Response response;
    const auto status = co_await RPC::request(*grpc_context_, probe_service_stub_, client_context, request, response);
    if (not status.ok())
    {
        co_return std::unexpected{grpc_status2result(status)};
    }
    co_return {};
}

AsyncResult<std::vector<ObjectReference>> ProbeServiceImpl::query_top_level_views()
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncGetViews>;
    grpc::ClientContext client_context;
    configure_client_context(client_context);

    RPC::Request request;
    RPC::Response response;
    const auto status = co_await RPC::request(*grpc_context_, probe_service_stub_, client_context, request, response);
    if (not status.ok())
    {
        co_return std::unexpected(grpc_status2result(status));
    }
    std::vector<ObjectReference> objects;
    for (auto &&object : response.object())
    {
        objects.emplace_back(ObjectReference{.object_id = object.object_id(), .type_id = object.type_id()});
    }
    co_return objects;
}

AsyncResult<entt::meta_any> ProbeServiceImpl::invoke_method(ObjectId id,
                                                            std::string method_name,
                                                            std::vector<entt::meta_any> parameters)
{
    using RPC = agrpc::ClientRPC<&proto::ProbeService::Stub::PrepareAsyncInvokeMethod>;
    grpc::ClientContext client_context;
    configure_client_context(client_context);

    RPC::Request request;
    request.set_object_id(id);
    auto *call = request.mutable_method_call();
    call->set_method_name(std::move(method_name));
    for (auto &&p : parameters)
    {
        *call->add_argument() = create_value(entt::locator<ValueRegistry>::value(), p);
    }

    RPC::Response response;
    const auto status = co_await RPC::request(*grpc_context_, probe_service_stub_, client_context, request, response);
    if (not status.ok())
    {
        co_return std::unexpected(grpc_status2result(status));
    }
    if (response.return_value().has_value())
    {
        co_return convert_value(
            entt::locator<ValueRegistry>::value(), *value_converter_, response.return_value().value());
    }
    co_return entt::meta_any{std::in_place_type<void>};
}
} // namespace quite::proto
