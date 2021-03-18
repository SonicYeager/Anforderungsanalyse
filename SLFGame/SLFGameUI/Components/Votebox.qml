import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "../Resources"
Rectangle {
    Layout.preferredWidth: 30
    Layout.preferredHeight: 30
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
