#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include <quite/disable_copy_move.hpp>
#include "quite/quite_client_export.hpp"

namespace quite
{
class Application;
using ApplicationPtr = std::shared_ptr<quite::Application>;

class QUITE_CLIENT_EXPORT ApplicationManager
{
  public:
    QUITE_DISABLE_COPY(ApplicationManager);
    ApplicationManager();
    ~ApplicationManager();
    ApplicationManager(ApplicationManager &&) noexcept = default;
    ApplicationManager &operator=(ApplicationManager &&) noexcept = default;

    ApplicationPtr create_host_application(const std::string &path_to_application,
                                           const std::vector<std::string> &args = {},
                                           const std::unordered_map<std::string, std::string> &environment = {});

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite
