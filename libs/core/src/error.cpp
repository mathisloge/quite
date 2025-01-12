#include "quite/error.hpp"

auto fmt::formatter<quite::ErrorCode>::format(quite::ErrorCode error_code, format_context &ctx) const
    -> format_context::iterator
{
    using quite::ErrorCode;
    string_view name = "unknown";
    switch (error_code)
    {
    case quite::ErrorCode::unknown:
        name = "unknown";
    case ErrorCode::aborted:
        name = "aborted";
        break;
    case quite::ErrorCode::cancelled:
        name = "cancelled";
        break;
    case quite::ErrorCode::invalid_argument:
        name = "invalid_argument";
        break;
    case quite::ErrorCode::deadline_exceeded:
        name = "deadline_exceeded";
        break;
    case quite::ErrorCode::not_found:
        name = "not_found";
        break;
    case quite::ErrorCode::failed_precondition:
        name = "failed_precondition";
        break;
    case quite::ErrorCode::unimplemented:
        name = "unimplemented";
        break;
    case quite::ErrorCode::unavailable:
        name = "unavailable";
        break;
    }
    return formatter<string_view>::format(name, ctx);
}

auto fmt::formatter<quite::Error>::format(const quite::Error &error, format_context &ctx) const
    -> format_context::iterator
{
    return fmt::format_to(ctx.out(), "(error_code: {}: message: {})", error.code, error.message);
}
