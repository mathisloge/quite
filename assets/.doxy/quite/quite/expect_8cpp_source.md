

# File expect.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**testing**](dir_5dc041d31cf4c8a741744373481e730f.md) **>** [**src**](dir_398cbba213cb2cd7b6578e890cc57257.md) **>** [**expect.cpp**](expect_8cpp.md)

[Go to the documentation of this file](expect_8cpp.md)


```C++
#include "quite/test/expect.hpp"
#include "expect_screenshot.hpp"
namespace quite::test
{

class RemoteObjectExpect : public IExpectBuilder
{
  public:
    RemoteObjectExpect(RemoteObject remote_object)
        : obj_{remote_object}
    {}

    bool to_have_screenshot(const std::string &name) override
    {
        if (has_screenshot_expect(name))
        {
            return verify_screenshot_expect(obj_, name);
        }
        create_screenshot_expect(obj_, name);
        return true;
    };

  private:
    RemoteObject obj_;
};

std::unique_ptr<IExpectBuilder> expect(RemoteObject remote_object)
{
    return std::make_unique<RemoteObjectExpect>(remote_object);
}
} // namespace quite::test
```


