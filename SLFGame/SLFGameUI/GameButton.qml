import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Rectangle {
    id: master
    Layout.preferredWidth: parent.width * 0.5
    Layout.preferredHeight: parent.height * 0.5
    radius: 90
    color: "white"
    property alias text: text.text
    property alias textColor: text.color
    property alias fontSize: text.font.pointSize
    Text {
        id: text
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.margins: 5
    }
    MouseArea {
        id: ma
        anchors.fill: parent
        hoverEnabled: true
    }
    states : [
        State {
            name: "greenButton"
            PropertyChanges {
                target: master
                color: "green"
            }
            PropertyChanges {
                target: ma
                onEntered: {
                    master.color = "green" + "#002000"
                }
                onExited: {
                    master.color = "green"
                }
            }
        },
        State {
            name: "redButton"
            PropertyChanges {
                target: master
                color: "#a11806"
            }
            PropertyChanges {
                target: ma
                onEntered: {
                    master.color = "#bb1806"
                }
                onExited: {
                    master.color = "#a11806"
                }
            }
        },
        State {
            name: "blueButton"
            PropertyChanges {
                target: master
                color: "#062e63"
            }
            PropertyChanges {
                target: ma
                onEntered: {
                    master.color = "#062eaa"
                }
                onExited: {
                    master.color = "#062e63"
                }
            }
        }
    ]
}
