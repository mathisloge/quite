#include "property_collector.hpp"
#include <QMetaProperty>
#include <QtQml/private/qqmldata_p.h>
#include <QtQml/private/qqmlmetatype_p.h>
#include <private/qv4executablecompilationunit_p.h>
#include <spdlog/spdlog.h>

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
        spdlog::debug("before QQmlData::get");
        auto data = QQmlData::get(object);
        if (not data or not data->compilationUnit)
        {
            spdlog::warn("got no data for qml object");
        }
        else
        {
            const auto qml_type = QQmlMetaType::qmlType(data->compilationUnit->url());
            if (qml_type.isValid())
            {
                meta_object = qml_type.metaObject();
            }
            else
            {
                spdlog::warn("qml type not valid");
            }
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
            // const QByteArray sig = QByteArray("2") + prop.notifySignal().methodSignature();
            //  QObject::connect(o, sig, this, SLOT(propertyChanged()));
        }
        if (prop.isReadable())
        {
            try
            {
                spdlog::debug("Read prop {}", prop.name());
                if (prop.name() == std::string{"inputDirection"} || prop.name() == std::string{"locale"} ||
                    prop.name() == std::string{"fontInfo"})
                {
                    continue;
                }
                properties.emplace(prop.name(), prop.read(object_meta.object).toString().toStdString());
            }
            catch (const std::exception &exception)
            {
                spdlog::error("could not add prop={}", exception.what());
            }
        }
        else
        {
            spdlog::debug("Property not readable");
        }
    }
    return properties;
}

} // namespace quite
