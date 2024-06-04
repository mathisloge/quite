#pragma once
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
    AutConnector aut_connector_;
};
} // namespace quite::ide
