pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    width: 720
    height: 420
    visible: true

    ListModel {
        id: todoModel
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        anchors.margins: 10

        RowLayout {
            Layout.fillWidth: true

            Button {
                objectName: "addButton"
                text: "+"
                onClicked: {
                    if (inputField.text.trim() !== "") {
                        todoModel.append({
                            title: inputField.text
                        });
                        inputField.text = "";
                    }
                }
            }

            TextField {
                objectName: "inputField"
                id: inputField
                Layout.fillWidth: true
                placeholderText: "Add a new task..."
            }
        }

        ListView {
            id: listView
            objectName: "listView"
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: todoModel

            delegate: SwipeDelegate {
                id: swipeDelegate
                required property string title
                required property int index

                width: listView.width
                text: title

                ListView.onRemove: removeAnimation.start()

                SequentialAnimation {
                    id: removeAnimation

                    PropertyAction {
                        target: swipeDelegate
                        property: "ListView.delayRemove"
                        value: true
                    }
                    NumberAnimation {
                        target: swipeDelegate
                        property: "height"
                        to: 0
                        easing.type: Easing.InOutQuad
                    }
                    PropertyAction {
                        target: swipeDelegate
                        property: "ListView.delayRemove"
                        value: false
                    }
                }

                swipe.left: Label {
                    text: qsTr("Edit")
                    color: "white"
                    verticalAlignment: Label.AlignVCenter
                    padding: 12
                    height: parent?.height
                    anchors.left: parent?.left

                    SwipeDelegate.onClicked: {
                        inputField.text = swipeDelegate.title;
                        todoModel.remove(swipeDelegate.index);
                    }

                    background: Rectangle {
                        color: SwipeDelegate.pressed ? Qt.darker("deepskyblue", 1.1) : "deepskyblue"
                    }
                }

                swipe.right: Label {
                    id: deleteLabel
                    text: qsTr("Delete")
                    color: "white"
                    verticalAlignment: Label.AlignVCenter
                    padding: 12
                    height: parent?.height
                    anchors.right: parent?.right

                    SwipeDelegate.onClicked: listView.model.remove(swipeDelegate.index)

                    background: Rectangle {
                        color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
                    }
                }
            }
        }
    }
}
