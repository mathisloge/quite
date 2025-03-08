#pragma once
#include <chrono>
#include <memory>
#include <quite/disable_copy_move.hpp>
#include "quite/quite_test_export.hpp"
#include "remote_object.hpp"

namespace quite
{
class Application;
class ObjectQuery;

namespace test
{
class ApplicationManager;
class QUITE_TEST_EXPORT Application
{
  public:
    QUITE_DISABLE_COPY(Application);
    Application(Application &&) noexcept;
    Application &operator=(Application &&) noexcept;
    ~Application();

    RemoteObject find_object(std::shared_ptr<ObjectQuery> query);
    RemoteObject try_find_object(std::shared_ptr<ObjectQuery> query, std::chrono::milliseconds timeout);
    void wait_for_connected(std::chrono::seconds timeout);
    void exit();

  private:
    friend ApplicationManager;
    explicit Application(std::shared_ptr<quite::Application> handle);

  private:
    std::shared_ptr<quite::Application> handle_;
};
} // namespace test
} // namespace quite
