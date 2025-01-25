#pragma once
#include <span>
#include <entt/meta/meta.hpp>
#include <quite/result.hpp>

namespace quite::probe
{
class ObjectTracker;
class MethodInvoker
{
  public:
    MethodInvoker(const ObjectTracker &object_tracker);

    Result<entt::meta_any> invoke_method(const entt::meta_any &object,
                                         std::string_view qualified_method_signature,
                                         std::span<entt::meta_any> params) const;

  private:
    const ObjectTracker &object_tracker_;
};
} // namespace quite::probe
