import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    objectName: "testRoot"
    width: 300; height: 200

    Text {
        id: "text"
        objectName: "testRoot2"
        anchors { bottom: parent.bottom; horizontalCenter: parent.horizontalCenter; bottomMargin: 20 }
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
}
