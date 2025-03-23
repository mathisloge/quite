#pragma once
#include <quite/async_result.hpp>
#include "basic_process_manager.hpp"

namespace quite::manager
{
class QUITE_MANAGER_EXPORT RemoteProcessManager : public BasicProcessManager
{
  public:
    /**
     * @brief Tries to fetch the remote environment from the connected process manager.
     *
     * @return AsyncResult<Environment>
     */
    AsyncResult<Environment> current_remote_environment();
};
} // namespace quite::manager
