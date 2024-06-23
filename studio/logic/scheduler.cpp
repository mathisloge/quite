#include "scheduler.hpp"
namespace quite::studio
{
stdexec::__loop::run_loop::__scheduler get_scheduler()
{
    static exec::single_thread_context thread_pool_;
    return thread_pool_.get_scheduler();
}
} // namespace quite::studio
