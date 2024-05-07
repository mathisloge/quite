import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import hello

Item {
    objectName: "testRoot"
    width: 300; height: 500

    Text {
        id: "text"
        objectName: "textArea"
        anchors { bottom: logview.top; horizontalCenter: parent.horizontalCenter; bottomMargin: 20 }
        text: "..."
    }
    RowLayout {
        Button {
            objectName: "helloBtn"
            text: "Hello"
            onClicked: text.text = "Hello"
        }
        Button {
            objectName: "worldBtn"
            text: "World"
            onClicked: text.text = "World"
        }
    }

    MyLogArea {
        objectName: "logArea"
        id: logArea
    }
    ScrollView {
        id: logview
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 200

        background: Rectangle {
            color: "grey"
        }
        TextArea {
            text: logArea.text
        }
    }
}
