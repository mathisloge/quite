#include "quite/manager/process_handle.hpp"
namespace quite::manager
{
ProcessHandle::ProcessHandle(std::shared_ptr<Process> app)
    : application_{std::move(app)}
{}

Process &ProcessHandle::instance()
{
    return *application_;
}

Process *ProcessHandle::operator->()
{
    return application_.get();
}
} // namespace quite::manager
