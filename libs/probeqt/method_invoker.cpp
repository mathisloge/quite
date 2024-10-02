#include "method_invoker.hpp"
#include <QDebug>
#include <QMetaMethod>
#include <ranges>

using namespace entt::literals;
namespace quite::probe
{
namespace
{
struct MetaValueDeleter
{
    QMetaType meta_type;
    void operator()(void *value) const
    {
        meta_type.destroy(value);
    }
};
} // namespace

MethodInvoker::MethodInvoker(const ObjectTracker &object_tracker)
    : object_tracker_{object_tracker}
{}

void MethodInvoker::invoke_method(const entt::meta_any &object,
                                  std::string_view qualified_method_signature,
                                  std::span<entt::meta_any> params) const
{
    const auto *object_ref = object.try_cast<QObject *>();
    if (object_ref != nullptr)
    {
        invoke_qmeta_method(*object_ref, qualified_method_signature, params);
    }
}

bool MethodInvoker::invoke_qmeta_method(QObject *obj,
                                        std::string_view qualified_method_signature,
                                        std::span<entt::meta_any> params) const
{
    auto &&meta_obj = obj->metaObject();
    const QByteArray normalized_method_signature = QMetaObject::normalizedSignature(qualified_method_signature.data());
    const auto method_index = meta_obj->indexOfMethod(normalized_method_signature);
    auto &&meta_method = meta_obj->method(method_index);
    if (method_index < 0)
    {
        return false;
    }

    using MetaValue = std::unique_ptr<void, MetaValueDeleter>;

    auto create_meta_value = [](QMetaType &&meta_type) -> MetaValue {
        MetaValueDeleter deleter{.meta_type = std::move(meta_type)};
        return MetaValue{deleter.meta_type.create(), std::move(deleter)};
    };
    std::vector<MetaValue> args{};
    args.emplace_back(std::forward<MetaValue>(create_meta_value(meta_method.returnMetaType())));

    // std::vector<QMetaMethodArgument> args;
    for (int i = 0; i < meta_method.parameterCount(); i++)
    {
        // auto &&proto_val = method_call_proto.argument(i);

        // REQUIRE(QMetaType::canConvert(from_value(proto_val), method_param));
        //  convert_to_value(protoval, method_param, param_val);
        // todo: copy values
        auto &&param_value = params[i];
        auto meta_type = param_value.type().func("metaType"_hs).invoke(param_value);
        auto param_value_meta = meta_type.cast<QMetaType>();
        auto meta_param = meta_method.parameterMetaType(i);

        auto &&value = args.emplace_back(create_meta_value(std::move(meta_param)));
        if (QMetaType::canConvert(param_value_meta, meta_param))
        {
            QMetaType::convert(param_value_meta, param_value.data(), meta_method.parameterMetaType(i), value.get());
        }
        else
        {
            qDebug() << "can't convert to" << param_value_meta << meta_param;
        }
    }

    std::vector<void *> meta_call_args;
    meta_call_args.reserve(args.size());

    std::ranges::copy(std::views::transform(args, [](auto &&val) { return val.get(); }),
                      std::back_inserter(meta_call_args));
    const auto call_result = obj->qt_metacall(QMetaObject::Call::InvokeMetaMethod, method_index, meta_call_args.data());

    // todo convert result type to any type
    qDebug() << QVariant::fromMetaType(meta_method.returnMetaType(), args[0].get());
    return call_result < 0;
}
} // namespace quite::probe