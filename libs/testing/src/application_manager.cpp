#include "quite/test/application_manager.hpp"
#include "quite/test/application.hpp"

namespace quite::test
{
Application ApplicationManager::create_host_application(const std::string &path_to_application,
                                                        const std::vector<std::string> &args,
                                                        const std::unordered_map<std::string, std::string> &environment)
{
    auto app = manager_.create_host_application(path_to_application, args, environment);
    return Application{std::move(app)};
}
} // namespace quite::test
