// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <entt/meta/container.hpp>
#include <qcontainerfwd.h>
namespace entt
{
template <typename... Args>
struct meta_sequence_container_traits<QList<Args...>> : basic_meta_sequence_container_traits<QList<Args...>>
{};

template <typename... Args>
struct meta_associative_container_traits<QMap<Args...>> : basic_meta_associative_container_traits<QMap<Args...>>
{};

template <typename... Args>
struct meta_associative_container_traits<QHash<Args...>> : basic_meta_associative_container_traits<QHash<Args...>>
{};
} // namespace entt
