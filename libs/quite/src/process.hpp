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

  private:
    pid_t pid_;
    std::array<int, 2> out_pipe_;
    std::array<int, 2> err_pipe_;
};
} // namespace quite
