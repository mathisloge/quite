// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <QMetaType>
namespace quite::probe
{
const QMetaObject *try_get_qt_meta_object(const QObject *object);
QMetaType try_get_qt_meta_type(const QMetaObject *meta_object);
QMetaType try_get_qt_meta_type(const QObject *object);
} // namespace quite::probe
