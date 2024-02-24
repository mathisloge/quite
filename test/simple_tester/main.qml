import QtQuick

Item {
    objectName: "testRoot"
    width: 300; height: 200

    Text {
        objectName: "testRoot2"
        anchors { bottom: parent.bottom; horizontalCenter: parent.horizontalCenter; bottomMargin: 20 }
        text: "Hello"
    }
}
