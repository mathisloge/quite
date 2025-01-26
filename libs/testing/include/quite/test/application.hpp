#pragma once
#include <memory>
#include <quite/disable_copy_move.hpp>
#include <quite/object_query.hpp>
#include "quite_test_export.hpp"
#include "remote_object.hpp"

namespace quite
{
class Application;

namespace test
{
class QUITE_TEST_EXPORT Application
{
  public:
    explicit Application(const std::string &application_path);

    QUITE_DISABLE_COPY(Application);
    Application(Application &&) noexcept;
    Application &operator=(Application &&) noexcept;
    ~Application();

    RemoteObject find_object(std::shared_ptr<ObjectQuery> query);
    void exit();

  private:
    explicit Application(std::shared_ptr<quite::Application> &&app);

  private:
    std::shared_ptr<quite::Application> app_;
};
} // namespace test
} // namespace quite
