#pragma once
#include <QPointingDevice>

namespace quite::probe
{

class MouseInjector final
{
  public:
    MouseInjector();
    ~MouseInjector();

    void click_object(QObject* target, QPointF local_click_point);

  private:
    QPointingDevice mouse_;
};
} // namespace quite::probe
