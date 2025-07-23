#include "quite/value/object_query.hpp"
#include <fmt/ranges.h>

namespace quite
{
ObjectQueryBuilder::ObjectQueryBuilder()
    : query_(std::make_shared<ObjectQuery>())
{}

ObjectQueryBuilder &ObjectQueryBuilder::with_property(
    std::initializer_list<std::pair<std::string, entt::meta_any>> props)
{
    for (const auto &[key, val] : props)
    {
        query_->properties.emplace(key, val);
    }
    return *this;
}

ObjectQueryBuilder &ObjectQueryBuilder::with_property(std::string key, std::int64_t value)
{
    query_->properties.insert_or_assign(std::move(key), std::move(value));
    return *this;
}

ObjectQueryBuilder &ObjectQueryBuilder::with_property(std::string key, std::uint64_t value)
{
    query_->properties.insert_or_assign(std::move(key), std::move(value));
    return *this;
}

ObjectQueryBuilder &ObjectQueryBuilder::with_property(std::string key, double value)
{
    query_->properties.insert_or_assign(std::move(key), std::move(value));
    return *this;
}

ObjectQueryBuilder &ObjectQueryBuilder::with_property(std::string key, bool value)
{
    query_->properties.insert_or_assign(std::move(key), std::move(value));
    return *this;
}

ObjectQueryBuilder &ObjectQueryBuilder::with_property(std::string key, std::string value)
{
    query_->properties.insert_or_assign(std::move(key), std::move(value));
    return *this;
}

ObjectQueryBuilder &ObjectQueryBuilder::with_parent(std::shared_ptr<ObjectQuery> parent)
{
    query_->container = std::move(parent);
    return *this;
}

ObjectQueryBuilder::operator std::shared_ptr<ObjectQuery>() const
{
    return query_;
}

ObjectQueryBuilder make_query()
{
    return ObjectQueryBuilder{};
}
} // namespace quite

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
