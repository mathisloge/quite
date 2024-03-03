#pragma once
#include <array>
#include <string>

namespace quite
{
class Process final
{
  public:
    explicit Process(const std::string &path_to_application);
    ~Process();

    int stdoutPipe() const noexcept;
    int stderrPipe() const noexcept;
    void terminate();

  private:
    pid_t pid_{-1};
    std::array<int, 2> out_pipe_{-1, -1};
    std::array<int, 2> err_pipe_{-1, -1};
};
} // namespace quite
