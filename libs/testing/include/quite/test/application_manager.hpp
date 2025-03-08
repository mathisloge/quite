#pragma once
#include <quite/application_manager.hpp>
#include <quite/disable_copy_move.hpp>
#include "quite/quite_test_export.hpp"

namespace quite
{
namespace test
{
class Application;
class QUITE_TEST_EXPORT ApplicationManager
{
  public:
    quite::test::Application create_host_application(
        const std::string &path_to_application,
        const std::vector<std::string> &args = {},
        const std::unordered_map<std::string, std::string> &environment = {});

  private:
    quite::ApplicationManager manager_;
};
} // namespace test
} // namespace quite
