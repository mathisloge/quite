#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/async_result.hpp>
#include <quite/meta/meta_types.hpp>
#include <quite/proto/meta_service.grpc.pb.h>

namespace quite::grpc_impl
{
AsyncResult<proto::MetaFindTypeResponse> make_meta_find_type(agrpc::GrpcContext &grpc_context,
                                                             proto::MetaService::Stub &stub,
                                                             meta::TypeId type_id);

} // namespace quite::grpc_impl
