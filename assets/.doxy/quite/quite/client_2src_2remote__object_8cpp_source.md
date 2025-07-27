

# File remote\_object.cpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**remote\_object.cpp**](client_2src_2remote__object_8cpp.md)

[Go to the documentation of this file](client_2src_2remote__object_8cpp.md)


```C++
#include <quite/client/remote_object.hpp>
namespace quite::client
{
RemoteObject::RemoteObject(ObjectId id)
    : id_{id}
{}

RemoteObject::~RemoteObject() = default;

ObjectId RemoteObject::id() const noexcept
{
    return id_;
}
} // namespace quite::client
```


