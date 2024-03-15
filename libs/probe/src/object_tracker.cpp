#include "object_tracker.hpp"
#include <QDebug>
#include <QMetaProperty>
#include <QThread>
#include <QVariant>
#include <QtQml/private/qqmldata_p.h>
#include <QtQml/private/qqmlmetatype_p.h>
#include <private/qv4executablecompilationunit_p.h>
#include <spdlog/spdlog.h>

namespace
{
void dump_props(QObject *obj)
{
    // QQmlContext *ctx = QQmlEngine::contextForObject(o);
    // if (!ctx || !ctx->engine())
    //     return;
    // qDebug() << "TEst" << ctx->nameForObject(const_cast<QObject *>(o));
    const QMetaObject *meta_object{nullptr};
    if (obj->metaObject())
    {
        meta_object = obj->metaObject();
        // auto collector = new QMetaPropertyCollector(obj);
    }
    else
    {
        auto data = QQmlData::get(obj);
        if (not data or not data->compilationUnit)
        {
        }
        else
        {
            spdlog::debug("track qml");
            const auto qml_type = QQmlMetaType::qmlType(data->compilationUnit->url());
            meta_object = qml_type.metaObject();
        }
    }
    if (meta_object)
    {
        const auto prop_count = meta_object->propertyCount();
        spdlog::debug("prop_count {}", prop_count);
    }
    else
    {
        spdlog::error("Could not get any meta object");
    }
    /*
        spdlog::debug("Properties of {}", obj->objectName().toStdString());
        do
        {
            spdlog::debug("Class {}", meta_object->className());
            std::vector<std::pair<QString, QVariant>> v;
            v.reserve(mo->propertyCount() - meta_object->propertyOffset());
            for (int i = mo->propertyOffset(); i < mo->propertyCount(); ++i)
                v.emplace_back(mo->property(i).name(), mo->property(i).read(o));
            // std::sort(v.begin(), v.end());
            for (const auto &i : v)
            {
                spdlog::debug("{} => {}", i.first.toStdString(), i.second.toString().toStdString());
            }
        } while ((mo = mo->superClass()));
*/
        const auto prop_count = meta_object->propertyCount();
        for (int i = 0; i < prop_count; ++i)
        {
            const auto prop{meta_object->property(i)};
            if (prop.hasNotifySignal())
            {
                const QByteArray sig = QByteArray("2") + prop.notifySignal().methodSignature();
                // QObject::connect(o, sig, this, SLOT(propertyChanged()));
            }
            spdlog::debug("Prop {} => {}", prop.name(), prop.read(obj).toString().toStdString());
        }
}

} // namespace
namespace quite
{

ObjectTracker::ObjectTracker()
{
    init_timer_.setInterval(0);
    init_timer_.setSingleShot(true);
    connect(&init_timer_, &QTimer::timeout, this, &ObjectTracker::processNewObjects);
}
ObjectTracker::~ObjectTracker() = default;

void ObjectTracker::processNewObjects()
{
    for (auto obj : objects_to_track_)
    {
        dump_props(obj);
    }
    objects_to_track_.clear();
}

void ObjectTracker::addObject(QObject *obj)
{
    if (own_ctx_)
    {
        return;
    }
    std::unique_lock l{locker_};
    own_ctx_ = true;
    connect(obj, &QObject::destroyed, this, [this, obj]() {
        std::unique_lock l{locker_};
        objects_to_track_.erase(obj);
    });
    objects_to_track_.emplace(obj);
    startTimer();
    own_ctx_ = false;
}
void ObjectTracker::removeObject(QObject *obj)
{}

void ObjectTracker::startTimer()
{
    if (init_timer_.isActive())
    {
        return;
    }
    //if (thread() == QThread::currentThread())
    //{
    //    init_timer_.start();
    //}
    //else
    //{
        static QMetaMethod m;
        if (m.methodIndex() < 0)
        {
            const auto idx = QTimer::staticMetaObject.indexOfMethod("start()");
            Q_ASSERT(idx >= 0);
            m = QTimer::staticMetaObject.method(idx);
            Q_ASSERT(m.methodIndex() >= 0);
        }
        m.invoke(&init_timer_, Qt::QueuedConnection);
    //}
}
} // namespace quite
