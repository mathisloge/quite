#include "mouse_action.hpp"
#include <QCoreApplication>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <spdlog/spdlog.h>
#include "../qtstdexec.h"

namespace quite::probe
{
exec::task<void> MouseActionRpcHandler::operator()(MouseActionRPC &rpc, const MouseActionRPC::Request &request)
{
    spdlog::trace("START RequestMouseAction={}", request.object_id());
    MouseActionRPC::Response response{};
    co_await stdexec::then(stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                           [&]() {
                               return mouse_injector.perform_action(request.object_id(),
                                                                    request.mouse_action(),
                                                                    request.mouse_button(),
                                                                    request.modifier_key(),
                                                                    request.relative_point());
                           });

    if (true)
    {
        co_await rpc.finish(response, grpc::Status::OK);
    }
    else
    {
        co_await rpc.finish(
            response, grpc::Status{grpc::StatusCode::NOT_FOUND, fmt::format("could not find {}", request.object_id())});
    }
}

agrpc::detail::RPCHandlerSender<MouseActionRPC, MouseActionRpcHandler> mouse_action(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service, MouseInjector &mouse_injector)
{
    return agrpc::register_sender_rpc_handler<MouseActionRPC>(
        grpc_context, service, MouseActionRpcHandler{mouse_injector});
}

} // namespace quite::probe
