#include "keyboard_injector.hpp"
#include <QKeyEvent>
namespace quite::probe
{
KeyboardInjector::KeyboardInjector()
{
    // https://codebrowser.dev/qt6/qtbase/src/testlib/qasciikey.cpp.html#_ZN5QTest10asciiToKeyEc
    QKeyEvent{QEvent::Type::KeyPress, Qt::Key_Shift, {}};
    QKeyEvent{QEvent::Type::KeyPress, Qt::Key_A, {}};
    QKeyEvent{QEvent::Type::KeyPress, Qt::Key_A, {}};
}
} // namespace quite::probe
