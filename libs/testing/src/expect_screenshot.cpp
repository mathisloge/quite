#include "expect_screenshot.hpp"
#include <quite/testing/verification_point.hpp>
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
