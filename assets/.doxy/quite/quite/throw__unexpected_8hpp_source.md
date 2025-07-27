

# File throw\_unexpected.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**testing**](dir_5dc041d31cf4c8a741744373481e730f.md) **>** [**src**](dir_398cbba213cb2cd7b6578e890cc57257.md) **>** [**throw\_unexpected.hpp**](throw__unexpected_8hpp.md)

[Go to the documentation of this file](throw__unexpected_8hpp.md)


```C++
#pragma once
#include <quite/result.hpp>
#include "quite/test/exceptions.hpp"
namespace quite::test
{
template <typename T>
constexpr void throw_unexpected(const Result<T> &result)
{
    if (not result.has_value())
    {
        throw RemoteException{result.error()};
    }
}
} // namespace quite::test
```


