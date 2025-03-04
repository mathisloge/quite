#include "quite/test/object_query_builder.hpp"
#include <memory>
#include <quite/value/object_query.hpp>

namespace quite::test
{
namespace
{
void insert_property(ObjectQuery &query, std::string key, entt::meta_any value)
{
    query.properties.insert_or_assign(std::move(key), std::move(value));
}
} // namespace

ObjectQueryBuilder::ObjectQueryBuilder()
    : query_{std::make_shared<ObjectQuery>()}
{}

ObjectQueryBuilder &ObjectQueryBuilder::set_parent(const ObjectQueryBuilder &parent)
{
    query_->container = parent.query_;
    return *this;
}

ObjectQueryBuilder &ObjectQueryBuilder::add_property(std::string key, std::int64_t value)
{
    insert_property(*query_, std::move(key), entt::forward_as_meta(value));
    return *this;
}

ObjectQueryBuilder &ObjectQueryBuilder::add_property(std::string key, double value)
{
    insert_property(*query_, std::move(key), entt::forward_as_meta(value));
    return *this;
}

ObjectQueryBuilder &ObjectQueryBuilder::add_property(std::string key, bool value)
{
    insert_property(*query_, std::move(key), entt::forward_as_meta(value));
    return *this;
}

ObjectQueryBuilder &ObjectQueryBuilder::add_property(std::string key, std::string value)
{
    insert_property(*query_, std::move(key), entt::forward_as_meta(std::move(value)));
    return *this;
}

std::shared_ptr<ObjectQuery> ObjectQueryBuilder::create()
{
    return query_;
}
} // namespace quite::test
