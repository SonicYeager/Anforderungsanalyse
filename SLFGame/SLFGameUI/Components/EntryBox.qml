import QtQuick 2.0
import QtQuick.Controls 2.5

TextField {
    id: entryBox
    selectByMouse: true
    color:"black"
    text: ""
    font.pixelSize: entryBox.height * 0.4
    implicitHeight : 50
    width: implicitWidth
    height: implicitHeight
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    hoverEnabled: true
    background: Rectangle{
        color:entryBox.hovered? "#cccccc" : "white"
        border.color:"#CCCCCC"
        border.width: 0.5
    }
    states : [
        State {
            name: "active"
            PropertyChanges {
                target:entryBox
                activeFocusOnPress: true
                background.color: entryBox.hovered? "#cccccc" : "white"
            }
        },
        State {
            name: "chatEntry"
            PropertyChanges {
                color:"black"
                target:entryBox
                activeFocusOnPress: true
                background.color: entryBox.hovered? "#d4d6d5" : "white"
                background.border.width: 2
                background.border.color: "#d4d6d5"
            }
        },
        State {
            name:"inactive"
            PropertyChanges {
                target: entryBox
                activeFocusOnPress: false
                background.color: "gray"
            }
        }
    ]
}
