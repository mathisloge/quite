#pragma once
#include <execpools/asio/asio_thread_pool.hpp>
#include "quite/quite_core_export.hpp"

namespace quite
{

/**
 * @brief Returns a reference to the global ASIO thread pool.
 *
 * This thread pool is managed as a singleton and is used for all asynchronous operations
 * that require an ASIO execution context within the quite framework.
 *
 * @return Reference to the global execpools::asio_thread_pool instance.
 */
QUITE_CORE_EXPORT execpools::asio_thread_pool &thread_pool();

/**
 * @brief Returns the executor associated with the global ASIO thread pool.
 *
 * This executor can be used to schedule tasks on the global thread pool.
 *
 * @return The executor object from the global thread pool.
 */
QUITE_CORE_EXPORT auto get_executor() -> decltype(thread_pool().get_executor());

} // namespace quite
