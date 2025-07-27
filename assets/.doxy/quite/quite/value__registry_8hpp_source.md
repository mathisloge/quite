

# File value\_registry.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**value**](dir_649c775d6fa8febbabfb9f60e7970e98.md) **>** [**value\_registry.hpp**](value__registry_8hpp.md)

[Go to the documentation of this file](value__registry_8hpp.md)


```C++
#pragma once
#include <entt/container/dense_map.hpp>
#include <entt/core/hashed_string.hpp>
#include <entt/locator/locator.hpp>
#include <entt/meta/context.hpp>
#include <entt/meta/meta.hpp>
#include "quite/quite_core_export.hpp"

namespace quite
{
class QUITE_CORE_EXPORT ValueRegistry
{
  public:
    using PropertyNameMap = entt::dense_map<entt::id_type, std::string>;

  public:
    entt::id_type named_property(std::string name);
    const PropertyNameMap &property_names() const;
    entt::meta_ctx &context() const;

  private:
    PropertyNameMap name_db_;
    entt::meta_ctx &context_ = entt::locator<entt::meta_ctx>::value_or();
};
} // namespace quite
```


