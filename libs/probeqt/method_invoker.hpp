#pragma once
#include <entt/meta/meta.hpp>
#include <quite/proto/methods.pb.h>
#include "object_tracker.hpp"
#include "result.hpp"
namespace quite::probe
{
struct MetaValueDeleter
{
    QMetaType meta_type;
    void operator()(void *value) const;
};

using MetaValuePtr = std::unique_ptr<void, MetaValueDeleter>;
struct MetaValueWrapper
{
    MetaValuePtr raw_value;
    entt::meta_any value;
};

class MethodInvoker
{
  public:
    MethodInvoker(const ObjectTracker &object_tracker);

    Result<MetaValueWrapper> invoke_method(const entt::meta_any &object,
                                           std::string_view qualified_method_signature,
                                           std::span<entt::meta_any> params) const;

  private:
    const ObjectTracker &object_tracker_;
};
} // namespace quite::probe
