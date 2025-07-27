

# File service\_handle.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**service\_handle.hpp**](service__handle_8hpp.md)

[Go to the documentation of this file](service__handle_8hpp.md)


```C++
#pragma once
#include <memory>

namespace quite
{

template <typename T>
class ServiceHandle
{
  public:
    using Type = T;

    ServiceHandle() = default;

    explicit ServiceHandle(std::shared_ptr<T> service)
        : service_{std::move(service)}
    {}

    template <typename... Args>
    explicit ServiceHandle(std::in_place_t /*_*/, Args &&...args)
        : service_{std::make_shared<T>(std::forward<Args>(args)...)}
    {}

    T *operator->() const
    {
        return service_.get();
    }

    T &operator*() const
    {
        return *service_;
    }

    explicit operator bool() const
    {
        return service_ != nullptr;
    }

  private:
    std::shared_ptr<T> service_;
};

} // namespace quite
```


