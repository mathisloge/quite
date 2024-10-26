#include "quite/errors.hpp"

auto fmt::formatter<quite::ErrorCode>::format(quite::ErrorCode error_code, format_context &ctx) const
    -> format_context::iterator
{
    using quite::ErrorCode;
    string_view name = "unknown";
    switch (error_code)
    {
    case ErrorCode::aborted:
        name = "aborted";
        break;
    }
    return formatter<string_view>::format(name, ctx);
}

auto fmt::formatter<quite::Error>::format(const quite::Error &error, format_context &ctx) const
    -> format_context::iterator
{
    return fmt::format_to(ctx.out(), "(error_code: {}: message: {})", error.code, error.message);
}
