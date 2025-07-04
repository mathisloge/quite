#include "quite/manager/process_handle.hpp"
namespace quite::manager
{
ProcessHandle::ProcessHandle(std::shared_ptr<Process> process)
    : process_{std::move(process)}
{}

Process &ProcessHandle::instance()
{
    return *process_;
}

Process *ProcessHandle::operator->()
{
    return process_.get();
}
} // namespace quite::manager
