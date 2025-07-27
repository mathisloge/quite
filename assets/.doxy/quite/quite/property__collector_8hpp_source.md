

# File property\_collector.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**property\_collector.hpp**](property__collector_8hpp.md)

[Go to the documentation of this file](property__collector_8hpp.md)


```C++
#pragma once
#include <QMetaObject>
#include <QObject>
#include <string>
#include <entt/meta/meta.hpp>
#include <quite/result.hpp>

namespace quite
{
struct ObjectMeta
{
    QObject *object;
    const QMetaObject *meta_object;

    [[nodiscard]] static ObjectMeta from_qobject(QObject *object);
};
[[nodiscard]] std::pair<std::string, entt::meta_any> read_property(QVariant property_value,
                                                                   const QMetaProperty &property);
Result<void> write_property(const ObjectMeta &meta,
                            const std::string &property_name,
                            const entt::meta_any &property_value);
[[nodiscard]] entt::dense_map<std::string, entt::meta_any> collect_properties(
    ObjectMeta object_meta, std::span<const std::string> property_names);

} // namespace quite
```


