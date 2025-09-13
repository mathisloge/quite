// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "MyLogArea.hpp"

void MyLogArea::setText(QString newText)
{
    text_.prepend('\n');
    text_.prepend(newText);
    Q_EMIT textChanged(text_);
}
