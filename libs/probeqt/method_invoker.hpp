#pragma once
#include <entt/meta/meta.hpp>
#include <quite/proto/methods.pb.h>
#include "object_tracker.hpp"
#include "result.hpp"
namespace quite::probe
{

class MethodInvoker
{
  public:
    MethodInvoker(const ObjectTracker &object_tracker);

    Result<entt::meta_any> invoke_method(const entt::meta_any &object,
                                         std::string_view qualified_method_signature,
                                         std::span<entt::meta_any> params) const;

  private:
    Result<entt::meta_any> invoke_qmeta_method(QObject *obj,
                                               std::string_view qualified_method_signature,
                                               std::span<entt::meta_any> params) const;

  private:
    const ObjectTracker &object_tracker_;
};
} // namespace quite::probe