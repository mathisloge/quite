// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <QObject>

class MyCustomType : public QObject
{
    Q_OBJECT

  public:
    double addition(double a, double b) const;
};
