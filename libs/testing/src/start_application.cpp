#include "quite/start_application.hpp"

namespace quite::test
{
ApplicationPtr start_application(const std::string &app_path)
{
    return Application::CreateApplication(app_path);
}
} // namespace quite::test
