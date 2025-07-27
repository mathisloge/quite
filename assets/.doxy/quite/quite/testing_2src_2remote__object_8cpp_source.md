

# File remote\_object.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**testing**](dir_5dc041d31cf4c8a741744373481e730f.md) **>** [**src**](dir_398cbba213cb2cd7b6578e890cc57257.md) **>** [**remote\_object.cpp**](testing_2src_2remote__object_8cpp.md)

[Go to the documentation of this file](testing_2src_2remote__object_8cpp.md)


```C++
#include "quite/test/remote_object.hpp"
#include <quite/client/remote_object.hpp>
#include "quite/test/property.hpp"
#include "throw_unexpected.hpp"

namespace quite::test
{

RemoteObject::RemoteObject(std::shared_ptr<client::RemoteObject> object)
    : object_{std::move(object)}
{}

void RemoteObject::mouse_action()
{
    const auto [action_result] = stdexec::sync_wait(object_->mouse_action()).value();
    throw_unexpected(action_result);
}

Image RemoteObject::take_snapshot()
{
    auto [snapshot] = stdexec::sync_wait(object_->take_snapshot()).value();
    throw_unexpected(snapshot);
    return std::move(snapshot.value());
}

void RemoteObject::invoke_method(std::string method_name)
{
    const auto [invoke_result] = stdexec::sync_wait(object_->invoke_method(std::move(method_name))).value();
    throw_unexpected(invoke_result);
}

Property RemoteObject::property(std::string name)
{
    auto [result] = stdexec::sync_wait(object_->property(std::move(name))).value();
    throw_unexpected(result);
    return Property{std::move(result.value())};
}

std::shared_ptr<client::RemoteObject> RemoteObject::underlying_object()
{
    return object_;
}

bool RemoteObject::operator==(const RemoteObject &rhs) const
{
    return this->object_ == rhs.object_;
}
} // namespace quite::test
```


