#pragma once
#include "quite/test/remote_object.hpp"
namespace quite::test
{

bool has_screenshot_expect(const std::string &name);
void create_screenshot_expect(RemoteObject obj, const std::string &name);
[[nodiscard]] bool verify_screenshot_expect(RemoteObject obj, const std::string &name);

} // namespace quite::test
