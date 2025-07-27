

# File property.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**include**](dir_69eac062172cc3dd38536daddef8f6c7.md) **>** [**quite**](dir_4b2f86ac1ca33b50681e1a9febdc0774.md) **>** [**client**](dir_7d6276c65eb2c4014d2f0c2cacdec3f0.md) **>** [**property.hpp**](client_2include_2quite_2client_2property_8hpp.md)

[Go to the documentation of this file](client_2include_2quite_2client_2property_8hpp.md)


```C++
#pragma once
#include <string>
#include <entt/meta/meta.hpp>
#include <fmt/core.h>
#include <quite/async_result.hpp>
#include <quite/disable_copy_move.hpp>
#include <quite/meta/meta_type_id.hpp>
#include "quite/quite_client_export.hpp"

namespace quite::client
{
class QUITE_CLIENT_EXPORT Property
{
  public:
    QUITE_DISABLE_COPY_MOVE(Property);
    Property() = default;
    virtual ~Property();
    virtual const std::string &name() const = 0;
    virtual meta::TypeId type_id() const = 0;
    virtual const Result<entt::meta_any> &value() const = 0;
    virtual AsyncResult<entt::meta_any> read() = 0;
    virtual AsyncResult<void> write(entt::meta_any value) = 0;
};

using PropertyPtr = std::shared_ptr<Property>;
} // namespace quite::client
```


