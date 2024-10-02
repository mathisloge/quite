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

    void invoke_method(const entt::meta_any &object,
                       std::string_view qualified_method_signature,
                       std::span<entt::meta_any> params) const;

  private:
    bool invoke_qmeta_method(QObject *obj,
                             std::string_view qualified_method_signature,
                             std::span<entt::meta_any> params) const;

  private:
    const ObjectTracker &object_tracker_;
};
} // namespace quite::probe