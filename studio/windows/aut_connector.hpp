#pragma once
#include <string>
#include "application_manager.hpp"

namespace quite::studio
{
class AutConnector final
{
  public:
   explicit AutConnector(std::shared_ptr<ApplicationManager> app_manager);
    void showConnectPopup();
    void connectPopup();

  private:
    std::shared_ptr<ApplicationManager> app_manager_;
    bool do_connect_popup_{false};
    std::string tmp_connect_popup_input_;
};
} // namespace quite::studio
