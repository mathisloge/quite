#pragma once
#include <exec/static_thread_pool.hpp>

namespace quite::studio
{
exec::static_thread_pool::scheduler get_scheduler();
}
