// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <QMetaObject>
#include <QObject>
#include <string>
#include <entt/meta/meta.hpp>
#include <quite/result.hpp>

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
Result<void> write_property(const ObjectMeta &meta,
                            const std::string &property_name,
                            const entt::meta_any &property_value);
[[nodiscard]] entt::dense_map<std::string, entt::meta_any> collect_properties(
    ObjectMeta object_meta, std::span<const std::string> property_names);

} // namespace quite
