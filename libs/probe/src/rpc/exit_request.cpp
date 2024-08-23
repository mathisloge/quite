#include "exit_request.hpp"
#include <QCoreApplication>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <quite/logger.hpp>
#include "../qtstdexec.h"

DEFINE_LOGGER(exit_request_logger)

namespace quite::probe
{
exec::task<void> ExitRpcHandler::operator()(ExitRPC &rpc, const ExitRPC::Request &request)
{
    LOG_DEBUG(exit_request_logger, "exit requested");
    ExitRPC::Response response{};
    co_await stdexec::then(stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                           [&]() { QCoreApplication::quit(); });
    co_await rpc.finish(response, grpc::Status::OK);
}

agrpc::detail::RPCHandlerSender<ExitRPC, ExitRpcHandler> exit_request(agrpc::GrpcContext &grpc_context,
                                                                      quite::proto::ProbeService::AsyncService &service)
{
    return agrpc::register_sender_rpc_handler<ExitRPC>(grpc_context, service, ExitRpcHandler{});
}
} // namespace quite::probe
