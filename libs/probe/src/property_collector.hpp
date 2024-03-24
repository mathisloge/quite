#pragma once
#include <string>
#include <unordered_map>

#include <QMetaObject>
#include <QObject>

namespace quite
{
struct ObjectMeta
{
    QObject *object;
    const QMetaObject *meta_object;

    [[nodiscard]] static ObjectMeta fromQObject(QObject *object);
};
[[nodiscard]]  std::unordered_map<std::string, std::string> collect_properties(ObjectMeta object_meta);

} // namespace quite
