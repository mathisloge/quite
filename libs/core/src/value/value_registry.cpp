#include "quite/value/value_registry.hpp"

namespace quite
{
entt::id_type ValueRegistry::named_property(std::string name)
{
    auto &&[emplaced_name, _] = name_db_.emplace(entt::hashed_string{name.c_str()}.value(), std::move(name));
    return emplaced_name->first;
}

const ValueRegistry::PropertyNameMap &ValueRegistry::property_names() const
{
    return name_db_;
}

entt::meta_ctx &ValueRegistry::context() const
{
    return context_;
}
} // namespace quite
