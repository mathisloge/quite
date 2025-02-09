#include "get_object_properties.hpp"
#include <QCoreApplication>
#include <QMetaProperty>
#include <QVariant>
#include <agrpc/register_sender_rpc_handler.hpp>
#include <entt/locator/locator.hpp>
#include <quite/logger.hpp>
#include <quite/proto/value.hpp>
#include <quite/value/value_registry.hpp>
#include "../property_collector.hpp"
#include "../qtstdexec.h"

DEFINE_LOGGER(get_obj_props_logger)

namespace quite::probe
{

exec::task<void> GetObjectPropertiesRpcHandler::operator()(GetObjectPropertiesRPC &rpc,
                                                           const GetObjectPropertiesRPC::Request &request)
{
    LOG_DEBUG(get_obj_props_logger(), "START RequestGetObjectProperty={}", request.object_id());
    GetObjectPropertiesRPC::Response response{};
    co_await stdexec::then(
        stdexec::schedule(QtStdExec::qThreadAsScheduler(QCoreApplication::instance()->thread())), [&]() {
            if (request.property_names_size() == 0)
            {
                auto obj = tracker.get_object_by_id(request.object_id());
                if (obj.has_value())
                {
                    auto properties = collect_properties(ObjectMeta::from_qobject(*obj));
                    auto *proto_values = response.mutable_property_values();
                    auto &value_registry = entt::locator<ValueRegistry>::value();
                    for (auto &&prop : properties)
                    {
                        proto_values->emplace(prop.first, proto::create_value(value_registry, prop.second));
                    }
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

                            auto &value_registry = entt::locator<ValueRegistry>::value();
                            response.mutable_property_values()->emplace(
                                std::move(prop.first), proto::create_value(value_registry, prop.second));
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
