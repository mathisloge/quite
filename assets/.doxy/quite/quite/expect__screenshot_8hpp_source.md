

# File expect\_screenshot.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**testing**](dir_5dc041d31cf4c8a741744373481e730f.md) **>** [**src**](dir_398cbba213cb2cd7b6578e890cc57257.md) **>** [**expect\_screenshot.hpp**](expect__screenshot_8hpp.md)

[Go to the documentation of this file](expect__screenshot_8hpp.md)


```C++
#pragma once
#include "quite/test/remote_object.hpp"
namespace quite::test
{

bool has_screenshot_expect(const std::string &name);
void create_screenshot_expect(RemoteObject obj, const std::string &name);
[[nodiscard]] bool verify_screenshot_expect(RemoteObject obj, const std::string &name);

} // namespace quite::test
```


