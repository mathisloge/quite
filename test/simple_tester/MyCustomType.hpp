#pragma once
#include <QObject>

class MyCustomType : public QObject
{
    Q_OBJECT

  public:
    double addition(double a, double b) const;
};
