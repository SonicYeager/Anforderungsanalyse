import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Rectangle {
    id: master
    Layout.preferredWidth: parent.width * 0.5
    Layout.preferredHeight: parent.height * 0.5
    radius: 0
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
            name: "blackButton"
            PropertyChanges {
                target: master
                color: "black"
            }
            PropertyChanges {
                target: ma
                onEntered: {
                    master.color = "#303030"
                }
                onExited: {
                    master.color = "black"
                }
            }
        },
        State {
            name: "whiteButton"
            PropertyChanges {
                target: master
                color: "white"
            }
            PropertyChanges {
                target: ma
                onEntered: master.color = "#d6d6d6"
                onExited: master.color = "white"
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
        },
        State {
            name: "inactive"
            PropertyChanges {
                target: master
                color: "gray"
            }
            PropertyChanges {
                target: ma
                hoverEnabled: false
            }
        }
    ]
}
