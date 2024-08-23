#include "process.hpp"
#include <csignal>
#include <quite/logger.hpp>
#include <spawn.h>
#include <sys/wait.h>

DEFINE_LOGGER(process_logger);

namespace quite
{
Process::Process(const std::string &path_to_application)
{
    if (pipe(out_pipe_.data()) == -1 || pipe(err_pipe_.data()) == -1)
    {
        LOG_ERROR(process_logger, "Could not open pipes for the application pipes");
        return;
    }

    // Konfiguriere posix_spawn-Attribute
    posix_spawn_file_actions_t file_actions;
    posix_spawn_file_actions_init(&file_actions);
    posix_spawn_file_actions_adddup2(&file_actions, out_pipe_[1], STDOUT_FILENO);
    posix_spawn_file_actions_adddup2(&file_actions, err_pipe_[1], STDERR_FILENO);
    posix_spawn_file_actions_addclose(&file_actions, out_pipe_[0]);
    posix_spawn_file_actions_addclose(&file_actions, err_pipe_[0]);

    const char *args[] = {path_to_application.c_str(), nullptr};
    if (posix_spawn(&pid_, args[0], &file_actions, nullptr, const_cast<char *const *>(args), environ) != 0)
    {
        LOG_ERROR(process_logger, "Could not spwan process {}", path_to_application);
        return;
    }

    // Schließe unbenutzte Enden der Pipes
    if (out_pipe_[1] != -1)
    {
        close(out_pipe_[1]);
        out_pipe_[1] = -1;
    }
    if (err_pipe_[1] != -1)
    {
        close(err_pipe_[1]);
        err_pipe_[1] = -1;
    }
}

int Process::stdoutPipe() const noexcept
{
    return out_pipe_[0];
}

int Process::stderrPipe() const noexcept
{
    return err_pipe_[0];
}

void Process::terminate()
{
    for (auto &pipe : out_pipe_)
    {
        if (pipe != -1)
        {
            close(pipe);
            pipe = -1;
        }
    }

    for (auto &pipe : err_pipe_)
    {
        if (pipe != -1)
        {
            close(pipe);
            pipe = -1;
        }
    }

    if (pid_ != -1)
    {
        kill(pid_, SIGTERM);
        int status{-1};
        if (waitpid(pid_, &status, 0) == -1)
        {
            LOG_ERROR(process_logger, "Error waiting for child process: {}", strerror(errno));
        }
        pid_ = -1;
    }
}

Process::~Process()
{
    terminate();
}
} // namespace quite
