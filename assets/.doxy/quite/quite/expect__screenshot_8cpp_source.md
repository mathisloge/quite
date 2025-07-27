

# File expect\_screenshot.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**testing**](dir_5dc041d31cf4c8a741744373481e730f.md) **>** [**src**](dir_398cbba213cb2cd7b6578e890cc57257.md) **>** [**expect\_screenshot.cpp**](expect__screenshot_8cpp.md)

[Go to the documentation of this file](expect__screenshot_8cpp.md)


```C++
#include "expect_screenshot.hpp"
#include <quite/client/testing/verification_point.hpp>
#include "throw_unexpected.hpp"

namespace quite::test
{
bool has_screenshot_expect(const std::string &name)
{
    return testing::has_verification_point(name);
}

void create_screenshot_expect(RemoteObject obj, const std::string &name)
{
    const auto [success] =
        stdexec::sync_wait(testing::create_verification_point(obj.underlying_object(), name)).value();
    throw_unexpected(success);
}

bool verify_screenshot_expect(RemoteObject obj, const std::string &name)
{
    const auto [success] =
        stdexec::sync_wait(testing::verify_verification_point(obj.underlying_object(), name)).value();
    throw_unexpected(success);
    return success.value();
}

} // namespace quite::test
```


