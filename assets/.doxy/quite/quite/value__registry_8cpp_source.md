

# File value\_registry.cpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**src**](dir_232ab8dc75117fda122ab855789b1b2c.md) **>** [**value**](dir_0eca0b5bd173d9114e1516dc11ca978d.md) **>** [**value\_registry.cpp**](value__registry_8cpp.md)

[Go to the documentation of this file](value__registry_8cpp.md)


```C++
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
```


