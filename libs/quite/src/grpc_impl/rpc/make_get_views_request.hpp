#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/async_result.hpp>
#include <quite/proto/probe.grpc.pb.h>

namespace quite::grpc_impl
{
AsyncResult<proto::GetViewsResponse> make_get_views_request(agrpc::GrpcContext &grpc_context,
                                                            proto::ProbeService::Stub &stub);

} // namespace quite::grpc_impl
