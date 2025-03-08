#include "quite/value/object_query.hpp"
#include <fmt/ranges.h>

template <>
struct fmt::formatter<entt::meta_any> : fmt::formatter<std::string_view>
{
    auto format(const entt::meta_any &any, format_context &ctx) const
    {
        return fmt::format_to(ctx.out(), "any[type_id={}, name={}]", any.type().id(), any.type().info().name());
    };
};

auto fmt::formatter<quite::ObjectQuery>::format(const quite::ObjectQuery &query, format_context &ctx) const
    -> format_context::iterator
{
    constexpr std::string_view kNoneStr{"none"};
    return fmt::format_to(ctx.out(),
                          "(container: {}: properties: [{}])",
                          query.container == nullptr ? kNoneStr : fmt::format("{}", *query.container),
                          fmt::join(query.properties, ":"));
}
