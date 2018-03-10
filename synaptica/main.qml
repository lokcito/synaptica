import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent
        color: "#3a4055"
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

        ListView {
            id: list
            width: 180; height: 200
            //orientation: ListView.Horizontal
            Component {
                id: actionItemsDelegate
                Rectangle {
                    id: wrapper
                    width: 180
                    height: 50
                    color: ListView.isCurrentItem ? "#21be2b" : "#4a526c"
                    Text {
                        id: contactInfo
                        width: 100
                        wrapMode: Text.Wrap
                        text: '<b>Name:</b> ' + name + '<div><b>Number:</b> ' + number + '</div>'
                        color: wrapper.ListView.isCurrentItem ? "white" : "black"
                    }
                    radius: 5
                    MouseArea {
                        anchors.fill: parent
                        onClicked: list.currentIndex = index
                    }
                }
            }
            model: ActionItemModel {}
            delegate: actionItemsDelegate
            //highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            focus: true
            onCurrentItemChanged: console.log(model.get(list.currentIndex).name + ' selected')
        }
    }
}
