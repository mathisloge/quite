#include "property_collector.hpp"
#include <QMetaProperty>
#include <QtQml/private/qqmldata_p.h>
#include <QtQml/private/qqmlmetatype_p.h>
#include <private/qv4executablecompilationunit_p.h>

namespace quite
{
ObjectMeta ObjectMeta::fromQObject(QObject *object)
{
    const QMetaObject *meta_object{nullptr};
    if (object->metaObject())
    {
        meta_object = object->metaObject();
        // auto collector = new QMetaPropertyCollector(obj);
    }
    else
    {
        auto data = QQmlData::get(object);
        if (not data or not data->compilationUnit)
        {
        }
        else
        {
            const auto qml_type = QQmlMetaType::qmlType(data->compilationUnit->url());
            meta_object = qml_type.metaObject();
        }
    }
    return ObjectMeta{.object = object, .meta_object = meta_object};
}

std::unordered_map<std::string, std::string> collect_properties(ObjectMeta object_meta)
{
    std::unordered_map<std::string, std::string> properties;
    const auto prop_count = object_meta.meta_object->propertyCount();
    for (int i = 0; i < prop_count; ++i)
    {
        const auto prop{object_meta.meta_object->property(i)};
        if (prop.hasNotifySignal())
        {
            const QByteArray sig = QByteArray("2") + prop.notifySignal().methodSignature();
            // QObject::connect(o, sig, this, SLOT(propertyChanged()));
        }
        properties.emplace(prop.name(), prop.read(object_meta.object).toString().toStdString());
    }
    return properties;
}

} // namespace quite
