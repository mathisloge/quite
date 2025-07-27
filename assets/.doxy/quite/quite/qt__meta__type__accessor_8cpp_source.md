

# File qt\_meta\_type\_accessor.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**probeqt**](dir_22ab9f3959c1273824a5221c73ee839d.md) **>** [**qt\_meta\_type\_accessor.cpp**](qt__meta__type__accessor_8cpp.md)

[Go to the documentation of this file](qt__meta__type__accessor_8cpp.md)


```C++
#include "qt_meta_type_accessor.hpp"
#include <QObject>
#include <QtQml/private/qqmldata_p.h>
#include <QtQml/private/qqmlmetatype_p.h>
#include <private/qv4executablecompilationunit_p.h>
#include <quite/logger.hpp>
#include "to_object_id.hpp"

DEFINE_LOGGER(qt_meta_type_accessor)

namespace quite::probe
{
const QMetaObject *try_get_qt_meta_object(const QObject *object)
{
    QPointer p{object};
    if (p.isNull())
    {
        LOG_DEBUG(qt_meta_type_accessor(), "Could not get a meta object from a null object");
        return nullptr;
    }

    const QMetaObject *meta_object{nullptr};
    if (object->metaObject() != nullptr)
    {
        return object->metaObject();
    }
    auto &&data = QQmlData::get(object);
    if (data != nullptr or not data->compilationUnit)
    {
        LOG_DEBUG(qt_meta_type_accessor(), "Could not get any data from object {}", to_object_id(object));
        return nullptr;
    }
    const auto qml_type = QQmlMetaType::qmlType(data->compilationUnit->url());
    if (qml_type.metaObject() == nullptr)
    {
        LOG_DEBUG(qt_meta_type_accessor(),
                  "Could not get QQmlMetaType from compilation unit. Object: {}",
                  to_object_id(object));
        return nullptr;
    }
    return qml_type.metaObject();
}

QMetaType try_get_qt_meta_type(const QMetaObject *meta_object)
{
    if (meta_object == nullptr)
    {
        LOG_DEBUG(qt_meta_type_accessor(), "Could get meta type from null object");
        return QMetaType{};
    }
    auto meta_type = meta_object->metaType();
    if (not meta_type.isValid())
    {
        LOG_DEBUG(qt_meta_type_accessor(), "Not a valid meta type, trying with the superclass");
        meta_type = try_get_qt_meta_type(meta_object->superClass());
    }
    return meta_type;
}

QMetaType try_get_qt_meta_type(const QObject *object)
{
    return try_get_qt_meta_type(try_get_qt_meta_object(object));
}
} // namespace quite::probe
```


