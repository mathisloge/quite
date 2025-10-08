// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import hello

Item {
    objectName: "testRoot"
    width: 300
    height: 500

    Text {
        id: "text"
        objectName: "textArea"
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
            bottomMargin: 20
        }
        text: "..."
    }
    RowLayout {
        Button {
            objectName: "helloBtn"
            text: "Hello"
            onClicked: text.text = "Hello"
            Layout.preferredWidth: 100
            Layout.preferredHeight: 30
        }
        Button {
            objectName: "worldBtn"
            text: "World"
            onClicked: text.text = "World"
        }
    }
}
