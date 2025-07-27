

# File exceptions.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**testing**](dir_5dc041d31cf4c8a741744373481e730f.md) **>** [**src**](dir_398cbba213cb2cd7b6578e890cc57257.md) **>** [**exceptions.cpp**](exceptions_8cpp.md)

[Go to the documentation of this file](exceptions_8cpp.md)


```C++
#include "quite/test/exceptions.hpp"
namespace quite::test
{
RemoteException::RemoteException(const Error &error)
    : std::runtime_error{error.message}
{}
} // namespace quite::test
```


