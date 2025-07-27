

# File result.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**result.hpp**](result_8hpp.md)

[Go to the documentation of this file](result_8hpp.md)


```C++
#pragma once
#include <expected>
#include "error.hpp"

namespace quite
{

template <typename T>
using Result = std::expected<T, Error>;

template <typename MessageT>
constexpr auto make_error_result(const ErrorCode code, MessageT &&message)
{
    return std::unexpected{Error{.code = code, .message = std::forward<MessageT>(message)}};
}

} // namespace quite
```


