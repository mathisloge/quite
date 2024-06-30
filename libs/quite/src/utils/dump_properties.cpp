#include "quite/utils/dump_properties.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace quite
{

struct ValueVisitor
{
    void operator()(auto &&value)
    {}

    void operator()(const std::shared_ptr<RemoteObject> &object)
    {}

    void operator()(const xyz::indirect<ArrayObject> &array)
    {}
};

AsyncResult<nlohmann::json> dump_properties(const RemoteObjectPtr &remote_object,
                                            const std::vector<std::string_view> &properties)
{
    nlohmann::json out;
    auto props = co_await remote_object->fetch_properties(properties);

    for (auto &&prop : *props)
    {
        std::visit(ValueVisitor{}, *prop.second->value());
    }

    co_return {};
}
} // namespace quite
