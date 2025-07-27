

# File meta\_qt\_containers.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**meta\_qt\_containers.hpp**](meta__qt__containers_8hpp.md)

[Go to the documentation of this file](meta__qt__containers_8hpp.md)


```C++
#pragma once
#include <entt/meta/container.hpp>
#include <qcontainerfwd.h>
namespace entt
{
template <typename... Args>
struct meta_sequence_container_traits<QList<Args...>> : basic_meta_sequence_container_traits<QList<Args...>>
{};

template <typename... Args>
struct meta_associative_container_traits<QMap<Args...>> : basic_meta_associative_container_traits<QMap<Args...>>
{};

template <typename... Args>
struct meta_associative_container_traits<QHash<Args...>> : basic_meta_associative_container_traits<QHash<Args...>>
{};
} // namespace entt
```


