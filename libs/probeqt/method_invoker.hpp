#pragma once
#include <entt/meta/meta.hpp>
#include <quite/proto/methods.pb.h>
#include "object_tracker.hpp"
namespace quite::probe
{
class MethodInvoker
{
  public:
    MethodInvoker(const ObjectTracker &object_tracker);

    auto invoke_method(const entt::meta_any &object,
                       std::string_view qualified_method_signature,
                       std::span<entt::meta_any> params)
    {
        const auto *object_ref = object.try_cast<QObject *>();
        if (object_ref != nullptr)
        {
            invoke_qmeta_method(*object_ref, qualified_method_signature, params);
        }
    }

  private:
    void invoke_qmeta_method(QObject *obj,
                             std::string_view qualified_method_signature,
                             std::span<entt::meta_any> params)
    {}

  private:
    const ObjectTracker &object_tracker_;
};
} // namespace quite::probe