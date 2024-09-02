#pragma once
#include <agrpc/grpc_context.hpp>
#include <quite/async_result.hpp>
#include <quite/proto/meta_service.grpc.pb.h>

namespace quite::grpc_impl
{
AsyncResult<proto::MetaObjectResponse> make_meta_service_get_meta_object(agrpc::GrpcContext &grpc_context,
                                                                         proto::MetaService::Stub &stub,
                                                                         std::string_view type_name);

} // namespace quite::grpc_impl
