#include "quite/utils/dump_properties.hpp"
#include <unordered_set>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

using json = nlohmann::json;
namespace quite
{
namespace
{
AsyncResult<nlohmann::json> dump_properties(std::unordered_set<ObjectId> &visited_objects,
                                            const RemoteObjectPtr &remote_object,
                                            const std::vector<std::string_view> &properties);

struct ValueVisitor
{
    std::unordered_set<ObjectId> &visited_objects;
    const std::vector<std::string_view> &properties;
    nlohmann::json &out;

    AsyncResult<void> operator()(auto &&value)
    {
        out = value;
        co_return {};
    }

    AsyncResult<void> operator()(const RemoteObjectPtr &object)
    {
        auto props = co_await dump_properties(visited_objects, object, properties);
        if (props.has_value())
        {
            out = props.value();
            co_return {};
        }
        co_return std::unexpected(props.error());
    }

    AsyncResult<void> operator()(const xyz::indirect<ArrayObject> &array)
    {
        out = nlohmann::json::array();
        for (auto &&value : array->values)
        {
            auto&& target = out.emplace_back(nlohmann::json::object());
            auto prop_result = co_await std::visit(ValueVisitor{visited_objects, properties, target}, value);
            if (not prop_result.has_value())
            {
                co_return std::unexpected(prop_result.error());
            }
        }
        co_return {};
    }
};

AsyncResult<nlohmann::json> dump_properties(std::unordered_set<ObjectId> &visited_objects,
                                            const RemoteObjectPtr &remote_object,
                                            const std::vector<std::string_view> &properties)
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
            auto prop_result =
                co_await std::visit(ValueVisitor{visited_objects, properties, out[prop.first]}, *prop.second->value());
            if (not prop_result.has_value())
            {
                co_return std::unexpected(prop_result.error());
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
AsyncResult<nlohmann::json> dump_properties(const RemoteObjectPtr &remote_object,
                                            const std::vector<std::string_view> &properties)
{
    std::unordered_set<ObjectId> objects;
    co_return co_await dump_properties(objects, remote_object, properties);
}
} // namespace quite
