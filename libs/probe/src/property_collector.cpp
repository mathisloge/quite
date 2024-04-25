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
    spdlog::error("has meta={}", object_meta.meta_object != nullptr);
    const auto prop_count = object_meta.meta_object->propertyCount();
    for (int i = 0; i < prop_count; ++i)
    {
        spdlog::debug("access prop at {}", i);
        const auto prop{object_meta.meta_object->property(i)};
        if(std::string_view{"remainingTime"} == prop.name()) {
            continue;
        }
        spdlog::debug("got prop at {}", prop.name());
        if (prop.hasNotifySignal())
        {
            spdlog::debug("prop has signal");
            // const QByteArray sig = QByteArray("2") + prop.notifySignal().methodSignature();
            //  QObject::connect(o, sig, this, SLOT(propertyChanged()));
        }
        spdlog::debug("emplace prop {}", object_meta.object != nullptr);
        try
        {
            spdlog::debug("prop {} is readable={}",prop.name(), prop.isReadable());
            prop.read(object_meta.object);
            //properties.emplace(prop.name(), prop.read(object_meta.object).toString().toStdString());
        }
        catch (const std::exception &exception)
        {
            spdlog::error("could not add prop={}", exception.what());
        }
        spdlog::debug("prop emplaced");
    }
    spdlog::debug("ret props");
    return properties;
}

} // namespace quite
