// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <QObject>
#include <QtQmlIntegration>

class MyLogArea : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString text WRITE setText READ getText NOTIFY textChanged)
  public:
    using QObject::QObject;

    QString getText() const
    {
        return text_;
    }
  public Q_SLOTS:
    void setText(QString newText);
  Q_SIGNALS:
    void textChanged(const QString &newText);

  private:
    QString text_;
};
