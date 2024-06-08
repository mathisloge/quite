#pragma once
#include <quite/application.hpp>
namespace quite::studio
{

class ApplicationManager
{
  public:
    void addApplication(const std::string &application);

  private:
    std::vector<std::shared_ptr<Application>> applications_;
};
} // namespace quite::studio
