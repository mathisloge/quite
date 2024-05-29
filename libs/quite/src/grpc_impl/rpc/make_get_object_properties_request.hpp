#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/async_result.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include <quite/remote_object.hpp>

namespace quite::grpc_impl
{
AsyncResult<proto::GetObjectPropertiesResponse> make_get_object_properties_request(
    agrpc::GrpcContext &grpc_context,
    proto::ProbeService::Stub &stub,
    ObjectId id,
    const std::vector<std::string_view> &properties);
} // namespace quite::grpc_impl
