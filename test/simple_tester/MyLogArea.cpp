#include "MyLogArea.hpp"

void MyLogArea::setText(QString newText)
{
    text_.prepend('\n');
    text_.prepend(newText);
    Q_EMIT textChanged(text_);
}
