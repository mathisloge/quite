

# File to\_object\_id.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**to\_object\_id.hpp**](to__object__id_8hpp.md)

[Go to the documentation of this file](to__object__id_8hpp.md)


```C++
#pragma once
#include <quite/value/object_id.hpp>

class QObject;
namespace quite::probe
{
constexpr ObjectId to_object_id(const QObject *obj)
{
    return reinterpret_cast<std::uintptr_t>(obj);
}

constexpr QObject *from_object_id(ObjectId obj_id)
{
    return reinterpret_cast<QObject *>(obj_id);
}
} // namespace quite::probe
```


