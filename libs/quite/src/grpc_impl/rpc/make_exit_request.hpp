#pragma once
#include <agrpc/client_rpc.hpp>
#include <agrpc/grpc_context.hpp>
#include <quite/async_result.hpp>
#include <quite/proto/probe.grpc.pb.h>

namespace quite::grpc_impl
{
AsyncResult<proto::ExitReponse> make_exit_request(agrpc::GrpcContext &grpc_context, proto::ProbeService::Stub &stub);
} // namespace quite::grpc_impl
