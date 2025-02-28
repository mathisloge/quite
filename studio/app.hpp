#pragma once
#include <exec/static_thread_pool.hpp>
#include "application_manager.hpp"
#include "windows/aut_connector.hpp"

namespace quite::studio
{
class App final
{
  public:
    explicit App();
    void setup();
    void show();

  private:
    void load_fonts();
    void showMainMenu();

  private:
    exec::static_thread_pool thread_pool_{1};
    exec::static_thread_pool::scheduler scheduler_{thread_pool_.get_scheduler()};
    std::shared_ptr<ApplicationManager> app_manager_{std::make_shared<ApplicationManager>()};
    AutConnector aut_connector_{app_manager_};
};
} // namespace quite::studio
