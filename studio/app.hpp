#pragma once
#include "application_manager.hpp"
#include "windows/aut_connector.hpp"

namespace quite::studio
{
class App final
{
  public:
    void show();

  private:
    void showMainMenu();

  private:
    std::shared_ptr<ApplicationManager> app_manager_{std::make_shared<ApplicationManager>()};
    AutConnector aut_connector_{app_manager_};
};
} // namespace quite::studio
