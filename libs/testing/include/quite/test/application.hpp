#pragma once
#include <memory>
#include <quite/disable_copy_move.hpp>
#include "quite_test_export.hpp"

namespace quite
{
class Application;

namespace test
{
class QUITE_TEST_EXPORT TestApplication
{
  public:
    static TestApplication start_application(const std::string &program_path);

    QUITE_DISABLE_COPY(TestApplication);
    TestApplication(TestApplication &&) noexcept;
    TestApplication &operator=(TestApplication &&) noexcept;
    ~TestApplication();

  private:
    explicit TestApplication(std::shared_ptr<Application> &&app);

  private:
    std::shared_ptr<Application> app_;
};
} // namespace test
} // namespace quite
