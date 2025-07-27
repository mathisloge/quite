

# File dump\_properties.cpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**src**](dir_e2c39676c5a8632601778e1e1ba34ff3.md) **>** [**utils**](dir_5d73f1c58d7ce353e6ce404cafa32f0a.md) **>** [**dump\_properties.cpp**](dump__properties_8cpp.md)

[Go to the documentation of this file](dump__properties_8cpp.md)


```C++
#include "quite/client/utils/dump_properties.hpp"
#include <unordered_set>
#include <nlohmann/json.hpp>
#include <quite/meta_any_formatter.hpp>

using json = nlohmann::json;

namespace quite
{
void to_json(json &j, const GenericClass &v);
}

namespace entt
{
void to_json(json &j, const entt::meta_any &v)
{
    const auto type = v.type();

    if (type.info() == entt::type_id<quite::GenericClass>())
    {
        j = v.cast<quite::GenericClass>();
    }
    else
    {
        j = json{{"unkown_value_type", type.info().name()}};
    }
}
} // namespace entt
namespace quite
{
void to_json(json &j, const GenericClass &v)
{
    j = json{v.properties};
}
namespace client
{
namespace
{

AsyncResult<nlohmann::json> dump_properties(std::unordered_set<ObjectId> &visited_objects,
                                            RemoteObjectPtr remote_object,
                                            std::vector<std::string> properties);

AsyncResult<nlohmann::json> dump_properties(std::unordered_set<ObjectId> &visited_objects,
                                            RemoteObjectPtr remote_object,
                                            std::vector<std::string> properties)
{
    if (visited_objects.contains(remote_object->id()))
    {
        co_return nlohmann::json{};
    }
    visited_objects.emplace(remote_object->id());

    nlohmann::json out = nlohmann::json::object();
    auto props = co_await remote_object->fetch_properties(properties);
    if (not props.has_value())
    {
        co_return std::unexpected(props.error());
    }

    for (auto &&prop : *props)
    {
        if (prop.second->value().has_value())
        {
            auto any_json = prop.second->value();
            if (any_json)
            {
                out[prop.first] = any_json.value();
            }
            else
            {
                co_return make_error_result(ErrorCode::invalid_argument,
                                            fmt::format("Could not create json from {}", *prop.second->value()));
            }
        }
        else
        {
            out[prop.first] = nlohmann::json{};
        }
    }

    co_return out;
}

} // namespace
AsyncResult<nlohmann::json> dump_properties(RemoteObjectPtr remote_object, std::vector<std::string> properties)
{
    std::unordered_set<ObjectId> objects;
    co_return co_await dump_properties(objects, std::move(remote_object), std::move(properties));
}
} // namespace client
} // namespace quite
```


