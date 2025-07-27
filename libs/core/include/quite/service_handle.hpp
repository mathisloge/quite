// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <memory>

namespace quite
{

/**
 * @brief A lightweight handle for accessing shared service instances.
 *
 * ServiceHandle provides pointer-like semantics for accessing services managed via std::shared_ptr.
 * It is intended to be used as a safe, convenient wrapper for dependency injection or service locator patterns.
 *
 * @tparam T The service type.
 */
template <typename T>
class ServiceHandle
{
  public:
    using Type = T;

    /**
     * @brief Constructs an empty ServiceHandle.
     */
    ServiceHandle() = default;

    /**
     * @brief Constructs a ServiceHandle from a shared_ptr to a service.
     * @param service The shared_ptr managing the service instance.
     */
    explicit ServiceHandle(std::shared_ptr<T> service)
        : service_{std::move(service)}
    {}

    /**
     * @brief Constructs a ServiceHandle with a new service instance.
     * @tparam Args Types of arguments to pass to the service constructor.
     * @param args Arguments to construct the service instance.
     */
    template <typename... Args>
    explicit ServiceHandle(std::in_place_t /*_*/, Args &&...args)
        : service_{std::make_shared<T>(std::forward<Args>(args)...)}
    {}

    /**
     * @brief Provides pointer-like access to the underlying service.
     * @return Pointer to the service instance, or nullptr if empty.
     */
    T *operator->() const
    {
        return service_.get();
    }

    /**
     * @brief Dereferences the handle to access the service instance.
     * @return Reference to the service instance.
     */
    T &operator*() const
    {
        return *service_;
    }

    /**
     * @brief Checks if the handle refers to a valid service.
     * @return true if the handle is non-empty, false otherwise.
     */
    explicit operator bool() const
    {
        return service_ != nullptr;
    }

  private:
    std::shared_ptr<T> service_;
};

} // namespace quite
