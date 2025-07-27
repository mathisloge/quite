

# File remote\_object.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**include**](dir_69eac062172cc3dd38536daddef8f6c7.md) **>** [**quite**](dir_4b2f86ac1ca33b50681e1a9febdc0774.md) **>** [**client**](dir_7d6276c65eb2c4014d2f0c2cacdec3f0.md) **>** [**remote\_object.hpp**](client_2include_2quite_2client_2remote__object_8hpp.md)

[Go to the documentation of this file](client_2include_2quite_2client_2remote__object_8hpp.md)


```C++
#pragma once
#include <cstdint>
#include <exec/task.hpp>
#include <quite/async_result.hpp>
#include "property.hpp"
#include "quite/image.hpp"
#include "quite/quite_client_export.hpp"
namespace quite::client
{

using ObjectId = std::uint64_t;

class QUITE_CLIENT_EXPORT RemoteObject
{
  public:
    explicit RemoteObject(ObjectId id);
    virtual ~RemoteObject();

    ObjectId id() const noexcept;

    virtual meta::TypeId type_id() const = 0;

    virtual AsyncResult<std::unordered_map<std::string, PropertyPtr>> fetch_properties(
        std::vector<std::string> properties) = 0;

    virtual AsyncResult<PropertyPtr> property(std::string property_name) = 0;

    virtual AsyncResult<void> write_property(std::string property_name, entt::meta_any value) = 0;

    virtual AsyncResult<void> mouse_action() = 0;

    virtual AsyncResult<Image> take_snapshot() = 0;

    virtual AsyncResult<void> invoke_method(std::string method_name) = 0;

  private:
    const ObjectId id_;
};
using RemoteObjectPtr = std::shared_ptr<RemoteObject>;
} // namespace quite::client
```


