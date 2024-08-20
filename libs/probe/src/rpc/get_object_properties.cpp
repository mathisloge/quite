#include "get_object_properties.hpp"
#include <QCoreApplication>
#include <QMetaProperty>
#include <QVariant>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <spdlog/spdlog.h>
#include "../property_collector.hpp"
#include "../qtstdexec.h"

namespace quite::probe
{

exec::task<void> GetObjectPropertiesRpcHandler::operator()(GetObjectPropertiesRPC &rpc,
                                                           const GetObjectPropertiesRPC::Request &request)
{
    spdlog::debug("START RequestGetObjectProperty={}", request.object_id());
    GetObjectPropertiesRPC::Response response{};
    co_await stdexec::then(
        stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())), [&]() {
            if (request.property_names_size() == 0)
            {
                auto obj = tracker.get_object_by_id(request.object_id());
                if (obj.has_value())
                {
                    auto properties = collect_properties(ObjectMeta::from_qobject(*obj));
                    response.mutable_property_values()->insert(properties.begin(), properties.end());
                }
                // todo: return error and make this a bit better code
            }
            else
            {
                for (auto &&property_name : request.property_names())
                {
                    auto obj_exp = tracker.get_object_by_id(request.object_id());
                    if (obj_exp.has_value())
                    {
                        auto &&obj = obj_exp.value();
                        auto meta_obj = ObjectMeta::from_qobject(obj);
                        const auto property_index = meta_obj.meta_object->indexOfProperty(property_name.c_str());
                        if (property_index >= 0)
                        {
                            auto meta_prop = meta_obj.meta_object->property(property_index);
                            auto prop = read_property(meta_prop.read(meta_obj.object), meta_prop);

                            response.mutable_property_values()->emplace(std::move(prop.first), std::move(prop.second));
                        }
                    }
                }
            }
        });
    co_await rpc.finish(response, grpc::Status::OK);
}

agrpc::detail::RPCHandlerSender<GetObjectPropertiesRPC, GetObjectPropertiesRpcHandler> get_object_properties(
    agrpc::GrpcContext &grpc_context, quite::proto::ProbeService::AsyncService &service, ObjectTracker &tracker)
{
    return agrpc::register_sender_rpc_handler<GetObjectPropertiesRPC>(
        grpc_context, service, GetObjectPropertiesRpcHandler{tracker});
}

} // namespace quite::probe
