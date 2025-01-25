#include "quite/test/application.hpp"
#include <quite/application.hpp>

namespace quite::test
{
TestApplication::~TestApplication() = default;

TestApplication::TestApplication(TestApplication &&) noexcept = default;

TestApplication &TestApplication::operator=(TestApplication &&) noexcept = default;

TestApplication TestApplication::start_application(const std::string &program_path)
{
    return TestApplication{Application::CreateApplication(program_path)};
}
} // namespace quite::test
