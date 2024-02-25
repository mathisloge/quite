#pragma once
#include <memory>
#include "quitelib_export.h"

namespace quite
{
class QUITELIB_EXPORT Application
{
  public:
    virtual ~Application();

  public:
    static std::shared_ptr<Application> createApplication(const std::string &path_to_application);
};
} // namespace quite
