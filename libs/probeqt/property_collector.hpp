#pragma once
#include <QMetaObject>
#include <QObject>
#include <string>
#include <entt/meta/meta.hpp>

namespace quite
{
struct ObjectMeta
{
    QObject *object;
    const QMetaObject *meta_object;

    [[nodiscard]] static ObjectMeta from_qobject(QObject *object);
};
[[nodiscard]] std::pair<std::string, entt::meta_any> read_property(QVariant property_value,
                                                                   const QMetaProperty &property);
[[nodiscard]] entt::dense_map<std::string, entt::meta_any> collect_properties(
    ObjectMeta object_meta, std::span<const std::string> property_names);

} // namespace quite
