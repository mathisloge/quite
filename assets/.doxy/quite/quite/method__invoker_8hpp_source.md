

# File method\_invoker.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**method\_invoker.hpp**](method__invoker_8hpp.md)

[Go to the documentation of this file](method__invoker_8hpp.md)


```C++
#pragma once
#include <span>
#include <entt/meta/meta.hpp>
#include <quite/result.hpp>
#include <quite/value/value_registry.hpp>

namespace quite::probe
{
class ObjectTracker;
class MethodInvoker
{
  public:
    MethodInvoker();

    Result<entt::meta_any> invoke_method(const entt::meta_any &object,
                                         std::string_view qualified_method_signature,
                                         std::span<entt::meta_any> params) const;
};
} // namespace quite::probe
```


