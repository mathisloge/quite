// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

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
