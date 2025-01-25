#include "quite/object_query.hpp"

auto fmt::formatter<quite::ObjectQuery>::format(const quite::ObjectQuery &query, format_context &ctx) const
    -> format_context::iterator
{
    constexpr std::string_view kNoneStr{"none"};
    return fmt::format_to(ctx.out(),
                          "(container: {}: properties: [{}])",
                          query.container == nullptr ? kNoneStr : fmt::format("{}", *query.container),
                          fmt::join(query.properties, ":"));
}
