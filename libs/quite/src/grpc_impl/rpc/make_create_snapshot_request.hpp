#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/async_result.hpp>
#include <quite/remote_object.hpp>
#include <quite/proto/probe.grpc.pb.h>

namespace quite::grpc_impl
{
AsyncResult<proto::ImageResponse> make_create_snapshot_request(agrpc::GrpcContext &grpc_context,
                                                                             proto::ProbeService::Stub &stub,
                                                                             ObjectId id);

} // namespace quite::grpc_impl
