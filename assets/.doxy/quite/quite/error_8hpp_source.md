

# File error.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**error.hpp**](error_8hpp.md)

[Go to the documentation of this file](error_8hpp.md)


```C++
#pragma once
#include <string>
#include <fmt/core.h>
#include "quite/quite_core_export.hpp"

namespace quite
{

enum class ErrorCode
{
    unknown,          
    cancelled,        
    invalid_argument, 
    deadline_exceeded,   
    not_found,           
    failed_precondition, 
    aborted,       
    unimplemented, 
    unavailable,   
};

struct Error
{
    ErrorCode code;
    std::string message;
};
} // namespace quite

template <>
struct QUITE_CORE_EXPORT fmt::formatter<quite::ErrorCode> : fmt::formatter<std::string_view>
{
    auto format(quite::ErrorCode error_code, format_context &ctx) const -> format_context::iterator;
};

template <>
struct QUITE_CORE_EXPORT fmt::formatter<quite::Error> : fmt::formatter<std::string_view>
{
    auto format(const quite::Error &error, format_context &ctx) const -> format_context::iterator;
};
```


