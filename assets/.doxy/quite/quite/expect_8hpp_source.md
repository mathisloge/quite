

# File expect.hpp

[**File List**](files.md) **>** [**include**](dir_0e3ab90749f7b4be0e4eb22d010aec3d.md) **>** [**quite**](dir_4b2197acd3cfc200796c46ec50ed103f.md) **>** [**test**](dir_e2259a6ae36431ad829e5c40f57eb4d8.md) **>** [**expect.hpp**](expect_8hpp.md)

[Go to the documentation of this file](expect_8hpp.md)


```C++
#pragma once
#include <memory>
#include "quite/quite_test_export.hpp"
#include "remote_object.hpp"

namespace quite::test
{
struct QUITE_TEST_EXPORT IExpectBuilder
{
    virtual ~IExpectBuilder() = default;
    virtual bool to_have_screenshot(const std::string &name) = 0;
};

[[nodiscard]] QUITE_TEST_EXPORT std::unique_ptr<IExpectBuilder> expect(RemoteObject remote_object);
} // namespace quite::test
```


