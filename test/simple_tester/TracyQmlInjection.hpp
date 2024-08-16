#pragma once
#include <qqmlintegration.h>
#include <qquickitem.h>

class TracyQmlInjection : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
  public:
    TracyQmlInjection();
    ~TracyQmlInjection() override;

  private:
    bool has_init_{false};
};
