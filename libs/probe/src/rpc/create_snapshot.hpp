#pragma once
#include <agrpc/detail/register_sender_rpc_handler.hpp>
#include <agrpc/grpc_context.hpp>
#include <agrpc/server_rpc.hpp>
#include <exec/task.hpp>
#include <quite/proto/probe.grpc.pb.h>
#include "../object_tracker.hpp"

namespace quite::probe
{
using CreateScreenshotRPC = agrpc::ServerRPC<&quite::proto::ProbeService::AsyncService::RequestCreateScreenshot>;
struct CreateScreenshotRpcHandler
{
    ObjectTracker &tracker;
    exec::task<void> operator()(CreateScreenshotRPC &rpc, const CreateScreenshotRPC::Request &request);
};

agrpc::detail::RPCHandlerSender<CreateScreenshotRPC, CreateScreenshotRpcHandler> create_snapshot(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service, ObjectTracker &tracker);
} // namespace quite::probe
