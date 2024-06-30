#pragma once
#include <QMetaObject>
#include <QObject>
#include <string>
#include <unordered_map>
#include <quite/proto/types.pb.h>

namespace quite
{
struct ObjectMeta
{
    QObject *object;
    const QMetaObject *meta_object;

    [[nodiscard]] static ObjectMeta from_qobject(QObject *object);
};
[[nodiscard]] std::pair<std::string, proto::Value> read_property(ObjectMeta &object_meta,
                                                                 const QMetaProperty &property);
[[nodiscard]] std::unordered_map<std::string, proto::Value> collect_properties(ObjectMeta object_meta);

} // namespace quite
