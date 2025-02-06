#pragma once
#include <array>
#include <string>
#include "quite/disable_copy_move.hpp"
#include "quite/quite_core_export.hpp"

namespace quite::details
{
class QUITE_CORE_EXPORT Process final
{
  public:
    QUITE_DISABLE_COPY_MOVE(Process);
    explicit Process(const std::string &path_to_application);
    ~Process();

    int stdout_pipe() const noexcept;
    int stderr_pipe() const noexcept;
    void terminate();

  private:
    pid_t pid_{-1};
    std::array<int, 2> out_pipe_{-1, -1};
    std::array<int, 2> err_pipe_{-1, -1};
};
} // namespace quite::details
