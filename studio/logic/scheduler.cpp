#include "scheduler.hpp"
namespace quite::studio
{
exec::static_thread_pool::scheduler get_scheduler()
{
    static exec::static_thread_pool thread_pool{2};
    return thread_pool.get_scheduler();
}
} // namespace quite::studio
