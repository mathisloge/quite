#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/async_result.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include <quite/remote_object.hpp>

namespace quite::grpc_impl
{
AsyncResult<proto::ImageResponse> make_create_snapshot_request(agrpc::GrpcContext &grpc_context,
                                                               proto::ProbeService::Stub &stub,
                                                               ObjectId id);

} // namespace quite::grpc_impl
