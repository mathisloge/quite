

# File qt\_meta\_type\_accessor.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**qt\_meta\_type\_accessor.hpp**](qt__meta__type__accessor_8hpp.md)

[Go to the documentation of this file](qt__meta__type__accessor_8hpp.md)


```C++
#pragma once
#include <QMetaType>
namespace quite::probe
{
const QMetaObject *try_get_qt_meta_object(const QObject *object);
QMetaType try_get_qt_meta_type(const QMetaObject *meta_object);
QMetaType try_get_qt_meta_type(const QObject *object);
} // namespace quite::probe
```


