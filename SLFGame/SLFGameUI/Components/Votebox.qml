import QtQuick 2.12
import QtQuick.Controls 2.12
import "../Resources"
Rectangle {
    width: 30
    height: 30
    color:Qt.rgba(0,0,0,0)
    Image{
        id: image
        anchors.fill: parent
        source: ""
        fillMode: Image.PreserveAspectFit
    }
    states: [
        State {
            name: "invalid"
            PropertyChanges {
                target: image
                source: "../Resources/cross.png"
                sourceSize.width: 1230
                sourceSize.height: 1280
            }
        },
        State {
            name: "valid"
            PropertyChanges {
                target: image
                source: "../Resources/tick.png"
                sourceSize.width: 800
                sourceSize.height: 800
            }
        }
    ]
}
