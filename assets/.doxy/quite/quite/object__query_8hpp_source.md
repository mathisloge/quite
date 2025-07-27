

# File object\_query.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**value**](dir_649c775d6fa8febbabfb9f60e7970e98.md) **>** [**object\_query.hpp**](object__query_8hpp.md)

[Go to the documentation of this file](object__query_8hpp.md)


```C++
#pragma once
#include <memory>
#include <entt/meta/meta.hpp>
#include <fmt/core.h>
#include "quite/quite_core_export.hpp"

namespace quite
{
class QUITE_CORE_EXPORT ObjectQueryBuilder;
struct QUITE_CORE_EXPORT ObjectQuery
{
    using PropertyMap = std::unordered_map<std::string, entt::meta_any>;
    std::shared_ptr<ObjectQuery> container; // use a shared pointer here, makes the python code gen much easier
    PropertyMap properties;
    std::string type_name;

    ObjectQuery() = default;
    ObjectQuery(const ObjectQuery &other) = default;
    ObjectQuery(ObjectQuery &&other) noexcept = default;
    ObjectQuery &operator=(const ObjectQuery &other) = default;
    ObjectQuery &operator=(ObjectQuery &&other) noexcept = default;
    ObjectQuery(const ObjectQueryBuilder &builder);
    ~ObjectQuery() = default;
};

class QUITE_CORE_EXPORT ObjectQueryBuilder
{
    std::shared_ptr<ObjectQuery> query_;

  public:
    ObjectQueryBuilder();

    ObjectQueryBuilder &with_property(std::initializer_list<std::pair<std::string, entt::meta_any>> props);

    ObjectQueryBuilder &with_property(std::string key, std::int64_t value);

    ObjectQueryBuilder &with_property(std::string key, std::uint64_t value);

    ObjectQueryBuilder &with_property(std::string key, double value);

    ObjectQueryBuilder &with_property(std::string key, bool value);

    ObjectQueryBuilder &with_property(std::string key, std::string value);

    ObjectQueryBuilder &with_parent(std::shared_ptr<ObjectQuery> parent);

    ObjectQueryBuilder &with_type(std::string type_name);

    operator std::shared_ptr<ObjectQuery>() const;

  private:
    friend ObjectQuery;
};

// Factory function
QUITE_CORE_EXPORT ObjectQueryBuilder make_query();

} // namespace quite
template <>
struct QUITE_CORE_EXPORT fmt::formatter<quite::ObjectQuery> : fmt::formatter<std::string_view>
{
    auto format(const quite::ObjectQuery &query, format_context &ctx) const -> format_context::iterator;
};
```


