#pragma once
#include <expected>
#include <agrpc/grpc_context.hpp>
#include <quite/async_result.hpp>
#include <quite/object_query.hpp>
#include <quite/proto/probe.grpc.pb.h>

namespace quite::grpc_impl
{
AsyncResult<proto::ObjectReply> make_find_object_request(agrpc::GrpcContext &grpc_context,
                                                         proto::ProbeService::Stub &stub,
                                                         const ObjectQuery &query);
} // namespace quite::grpc_impl
