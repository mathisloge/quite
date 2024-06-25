#include "get_object_properties.hpp"
#include <QCoreApplication>
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
    co_await stdexec::then(stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())),
                           [&]() {
                               if (request.property_names_size() == 0)
                               {
                                   auto obj = tracker.get_object_by_id(request.object_id());
                                   auto properties = collect_properties(ObjectMeta::from_qobject(*obj));
                                   response.mutable_property_values()->insert(properties.begin(), properties.end());
                               }
                               else
                               {
                                   for (auto &&property_name : request.property_names())
                                   {
                                       auto obj_exp = tracker.get_object_by_id(request.object_id());
                                       if (obj_exp.has_value())
                                       {
                                           auto &&obj = obj_exp.value();

                                           constexpr auto value_meta = QMetaType::fromType<proto::Value>();
                                           proto::Value value;
                                           auto prop = obj->property(property_name.c_str());
                                           const bool convertable = QMetaType::canConvert(prop.metaType(), value_meta);
                                           if (convertable)
                                           {
                                               QMetaType::convert(prop.metaType(), &prop, value_meta, &value);
                                           }
                                           else
                                           {
                                               *value.mutable_class_val()->mutable_type_name() = prop.typeName();
                                           }

                                           response.mutable_property_values()->emplace(property_name, std::move(value));
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
