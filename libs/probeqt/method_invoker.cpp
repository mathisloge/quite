// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "method_invoker.hpp"
#include <QDebug>
#include <QMetaMethod>
#include <ranges>
#include <entt/meta/resolve.hpp>
#include <fmt/format.h>
#include <quite/logger.hpp>

DEFINE_LOGGER(method_invoker)

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

Result<entt::meta_any> invoke_qmeta_method(entt::meta_ctx &meta_context,
                                           QObject *obj,
                                           std::string_view qualified_method_signature,
                                           std::span<entt::meta_any> params)
{
    auto &&meta_obj = obj->metaObject();
    const QByteArray normalized_method_signature = QMetaObject::normalizedSignature(qualified_method_signature.data());
    const auto method_index = meta_obj->indexOfMethod(normalized_method_signature);
    auto &&meta_method = meta_obj->method(method_index);
    if (method_index < 0)
    {
        return std::unexpected{Error{
            .code = ErrorCode::invalid_argument,
            .message =
                fmt::format("Could a method for {} of type {}", qualified_method_signature, meta_obj->className())}};
    }

    if (meta_method.parameterCount() != params.size())
    {
        return make_error_result(ErrorCode::failed_precondition,
                                 fmt::format("Method {} expects {} arguments but only {} were passed",
                                             qualified_method_signature,
                                             meta_method.parameterCount(),
                                             params.size()));
    }

    using MetaValue = std::unique_ptr<void, MetaValueDeleter>;

    auto create_meta_value = [](QMetaType meta_type) -> MetaValue {
        MetaValueDeleter deleter{.meta_type = std::move(meta_type)};
        return MetaValue{deleter.meta_type.create(), std::move(deleter)};
    };
    std::vector<MetaValue> args{};
    args.reserve(1 + meta_method.parameterCount());
    // return value ALWAYS at the first position
    args.emplace_back(create_meta_value(meta_method.returnMetaType()));

    for (int i = 0; i < meta_method.parameterCount(); i++)
    {
        const auto param_meta_type = meta_method.parameterMetaType(i);
        const auto &param_value = params[i];

        const QMetaType *any_meta_type = param_value.type().custom();

        // first try to convert with Qt. If that fails, try to convert with the custom meta system.
        if (any_meta_type != nullptr and QMetaType::canConvert(*any_meta_type, param_meta_type))
        {
            auto &&value = args.emplace_back(create_meta_value(param_meta_type));
            QMetaType::convert(*any_meta_type, param_value.base().data(), param_meta_type, value.get());
        }
        else if (auto param_meta_value =
                     param_value.allow_cast(entt::resolve(entt::hashed_string{param_meta_type.name()}.value()));
                 param_meta_value)
        {
            auto &&value = args.emplace_back(create_meta_value(param_meta_type));
            param_meta_value.type().from_void(value.get(), false).assign(std::move(param_value));
        }
        else
        {
            return make_error_result(ErrorCode::invalid_argument,
                                     fmt::format("Could convert arg {} with base type {} to type {}",
                                                 i,
                                                 param_value.type().info().name(),
                                                 param_meta_type.name()));
        }
    }

    std::vector<void *> meta_call_args;
    meta_call_args.reserve(args.size());

    std::ranges::copy(std::views::transform(args, [](auto &&val) { return val.get(); }),
                      std::back_inserter(meta_call_args));
    const auto call_result = obj->qt_metacall(QMetaObject::Call::InvokeMetaMethod, method_index, meta_call_args.data());

    LOG_DEBUG(method_invoker(), "Return type: {}", meta_method.returnMetaType().name());
    const auto custom_meta_type =
        entt::resolve(meta_context, entt::hashed_string{meta_method.returnMetaType().name()}.value());
    if (call_result < 0)
    {
        if (meta_method.returnMetaType() == QMetaType::fromType<void>())
        {
            return entt::meta_any{std::in_place_type<void>};
        }
        if (custom_meta_type)
        {
            constexpr bool kTransferOwnership{true};
            // args[0] is always the return type.
            return custom_meta_type.from_void(args[0].release(), kTransferOwnership);
        }
    }
    return make_error_result(ErrorCode::cancelled,
                             fmt::format("Could not invoke or wrap return type. Call status = {}, convertible = ",
                                         call_result,
                                         static_cast<bool>(custom_meta_type)));
}
} // namespace

MethodInvoker::MethodInvoker()
{}

Result<entt::meta_any> MethodInvoker::invoke_method(const entt::meta_any &object,
                                                    std::string_view qualified_method_signature,
                                                    std::span<entt::meta_any> params) const
{
    const auto *object_ref = object.try_cast<QObject *>();
    if (object_ref != nullptr)
    {
        auto &value_registy = entt::locator<ValueRegistry>::value_or();
        return invoke_qmeta_method(value_registy.context(), *object_ref, qualified_method_signature, params);
    }
    return make_error_result(ErrorCode::invalid_argument, "Could find a qobject for the given base type");
}
} // namespace quite::probe
