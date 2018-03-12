import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent
        color: "#3a4055"
/*
    Example
        Component {
             id: actionItemDelegate
             Item {
                 width: 180; height: 40
                 Column {
                     Text { text: '<b>Name:</b> ' + name }
                     Text { text: '<b>Number:</b> ' + number }
                 }
             }
         }
*/
        ListView {
            id: list
            width: 180; height: 200
            //orientation: ListView.Horizontal
            Component {
                id: actionItemsDelegate
                Rectangle {
                    id: wrapper
                    width: 100
                    height: 50
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: ListView.isCurrentItem ? "#21be2b" : "#424961"
                    anchors.left: parent.left
                    Text {
                        id: contactInfo
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        wrapMode: Text.Wrap
                        text: name
                        color: wrapper.ListView.isCurrentItem ? "white" : "#7680a2"
                    }
                    radius: 5
                    MouseArea {
                        anchors.fill: parent
                        onClicked: list.currentIndex = index
                    }
                }
            }
            spacing: 2
            model: ActionItemModel {}
            delegate: actionItemsDelegate
            //highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            focus: true
            onCurrentItemChanged: {
                clipboardManage.toClipboard(model.get(list.currentIndex).name)
            }
        }
    }
}
