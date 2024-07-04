#pragma once
#include <exec/static_thread_pool.hpp>
#include "application_manager.hpp"
#include "windows/aut_connector.hpp"

namespace quite::studio
{
class App final
{
  public:
    explicit App(SDL_Renderer *renderer);
    void show();

  private:
    void showMainMenu();

  private:
    SDL_Renderer *renderer_;
    exec::static_thread_pool thread_pool_{1};
    exec::static_thread_pool::scheduler scheduler_{thread_pool_.get_scheduler()};
    std::shared_ptr<ApplicationManager> app_manager_{std::make_shared<ApplicationManager>(renderer_)};
    AutConnector aut_connector_{app_manager_};
};
} // namespace quite::studio
