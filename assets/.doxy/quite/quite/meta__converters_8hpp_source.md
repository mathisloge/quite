

# File meta\_converters.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**meta\_converters.hpp**](meta__converters_8hpp.md)

[Go to the documentation of this file](meta__converters_8hpp.md)


```C++
#pragma once
#include <quite/meta/meta_types.hpp>
#include "quite/proto/meta.pb.h"
namespace quite::proto
{
meta::PrimitiveType from_protocol(const MetaPrimitiveType &type);
meta::ListType from_protocol(const MetaListType &type);
meta::MapType from_protocol(const MetaMapType &type);
meta::ObjectTypePtr from_protocol(const MetaObjectType &type);
meta::EnumTypePtr from_protocol(const MetaEnumType &type);

void to_protocol(const meta::Type &type, MetaType &proto);
} // namespace quite::proto
```


