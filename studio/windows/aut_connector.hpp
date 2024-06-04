#pragma once
#include <string>
namespace quite::studio
{
class AutConnector final
{
  public:
    void showConnectPopup();
    void connectPopup();

  private:
    bool do_connect_popup_{false};
    std::string tmp_connect_popup_input_;
};
} // namespace quite::studio
