#pragma once
#include <expected>
#include <agrpc/grpc_context.hpp>
#include <quite/async_result.hpp>
#include <quite/proto/probe.grpc.pb.h>

namespace quite::grpc_impl
{
AsyncResult<proto::ObjectReply> make_find_object_request(agrpc::GrpcContext &grpc_context,
                                                         proto::ProbeService::Stub &stub,
                                                         std::string_view object_name);
} // namespace quite::grpc_impl
