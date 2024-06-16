#pragma once
#include <quite/application.hpp>
namespace quite::studio
{
class ApplicationOverview
{
  public:
    ApplicationOverview(std::shared_ptr<Application> application);

  private:
    std::shared_ptr<Application> application_;
};
} // namespace quite::studio
