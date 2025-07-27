

# File value\_converters.cpp



[**FileList**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**value\_converters.cpp**](value__converters_8cpp.md)

[Go to the source code of this file](value__converters_8cpp_source.md)



* `#include "value_converters.hpp"`
* `#include <QColor>`
* `#include <QList>`
* `#include <QMetaType>`
* `#include <QObject>`
* `#include <QQmlListProperty>`
* `#include <QQmlListReference>`
* `#include <QQuickItem>`
* `#include <entt/meta/container.hpp>`
* `#include <entt/meta/factory.hpp>`
* `#include <entt/meta/meta.hpp>`
* `#include <private/qquickanchors_p_p.h>`
* `#include <quite/logger.hpp>`
* `#include <quite/value/generic_value_class.hpp>`
* `#include <quite/value/value_registry.hpp>`
* `#include "meta_qt_containers.hpp"`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**quite**](namespacequite.md) <br> |
| namespace | [**probe**](namespacequite_1_1probe.md) <br> |



















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**REGISTER\_QT\_TYPES\_FUNCTION**](value__converters_8cpp.md#define-register_qt_types_function) (TypeName, TypeId, Type) `register\_type&lt;Type&gt;(value\_registry, #Type);`<br> |

## Macro Definition Documentation





### define REGISTER\_QT\_TYPES\_FUNCTION 

```C++
#define REGISTER_QT_TYPES_FUNCTION (
    TypeName,
    TypeId,
    Type
) `register_type<Type>(value_registry, #Type);`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/probeqt/value_converters.cpp`

