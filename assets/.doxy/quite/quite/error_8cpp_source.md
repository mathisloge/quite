

# File error.cpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**src**](dir_232ab8dc75117fda122ab855789b1b2c.md) **>** [**error.cpp**](error_8cpp.md)

[Go to the documentation of this file](error_8cpp.md)


```C++
#include "quite/error.hpp"

auto fmt::formatter<quite::ErrorCode>::format(quite::ErrorCode error_code, format_context &ctx) const
    -> format_context::iterator
{
    return formatter<string_view>::format(
        [error_code]() {
            using quite::ErrorCode;
            switch (error_code)
            {
            case ErrorCode::unknown:
                return "unknown";
            case ErrorCode::aborted:
                return "aborted";
            case ErrorCode::cancelled:
                return "cancelled";
            case ErrorCode::invalid_argument:
                return "invalid_argument";
            case ErrorCode::deadline_exceeded:
                return "deadline_exceeded";
            case ErrorCode::not_found:
                return "not_found";
            case ErrorCode::failed_precondition:
                return "failed_precondition";
            case ErrorCode::unimplemented:
                return "unimplemented";
            case ErrorCode::unavailable:
                return "unavailable";
            }
            return "unknown";
        }(),
        ctx);
}

auto fmt::formatter<quite::Error>::format(const quite::Error &error, format_context &ctx) const
    -> format_context::iterator
{
    return fmt::format_to(ctx.out(), "(error_code: {}: message: {})", error.code, error.message);
}
```


