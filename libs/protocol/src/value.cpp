#include "quite/proto/value.hpp"
#include <ranges>
#include <entt/core/hashed_string.hpp>
#include <entt/meta/utility.hpp>
#include "quite/proto/traits.hpp"

using namespace entt::literals;

namespace quite::proto
{
namespace
{
void convert_class(const entt::dense_map<entt::hashed_string::hash_type, std::string> &property_name_db,
                   Value &value,
                   const entt::meta_any &any);
}
Value create_value(const entt::dense_map<entt::hashed_string::hash_type, std::string> &property_name_db,
                   const entt::meta_any &any)
{
    Value value;
    const auto type = any.type();
    if (type.is_class())
    {
        convert_class(property_name_db, value, any);
    }
    return value;
}

namespace
{
void convert_class(const entt::dense_map<entt::hashed_string::hash_type, std::string> &property_name_db,
                   Value &value,
                   const entt::meta_any &any)
{
    const auto type = any.type();
    const auto traits = type.traits<Traits>();

    auto *class_value = value.mutable_class_val();
    if (traits == Traits::unpack_properties)
    {
        auto &&properties = any.get("properties"_hs);
        for (auto &&[name, value] : properties.as_associative_container())
        {
            auto &&class_member = class_value->add_value();
            class_member->set_name(name.cast<std::string>());
            *class_member->mutable_value() = create_value(property_name_db, value);
        }
    }
    else
    {
        for (auto &&data_member : type.data())
        {
            auto it = property_name_db.find(data_member.first);
            if (it == property_name_db.end())
            {
                continue;
            }
            auto &&class_member = class_value->add_value();
            class_member->set_name(it->second);
            *class_member->mutable_value() = create_value(property_name_db, data_member.second.get(any));
        }
    }
}
} // namespace
} // namespace quite::proto
