

# File exceptions.hpp

[**File List**](files.md) **>** [**include**](dir_0e3ab90749f7b4be0e4eb22d010aec3d.md) **>** [**quite**](dir_4b2197acd3cfc200796c46ec50ed103f.md) **>** [**test**](dir_e2259a6ae36431ad829e5c40f57eb4d8.md) **>** [**exceptions.hpp**](exceptions_8hpp.md)

[Go to the documentation of this file](exceptions_8hpp.md)


```C++
#pragma once
#include <stdexcept>
#include <quite/error.hpp>
#include "quite/quite_test_export.hpp"

namespace quite::test
{
class QUITE_TEST_EXPORT RemoteException : public std::runtime_error
{
  public:
    explicit RemoteException(const Error &error);
};
} // namespace quite::test
```


