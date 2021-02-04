import QtQuick 2.9

Rectangle {
    id:textBox
    color:"white"
    border.color:"#CCCCCC"
    border.width: 0.5
    implicitWidth: text_name.implicitWidth
    implicitHeight : 50
    width: implicitWidth
    height: implicitHeight
    property alias text: text_name.text
    Text {
        id: text_name
        color:"black"
        font.pointSize: 14
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.margins: 5
    }
    MouseArea{
        anchors.fill:parent
        hoverEnabled: true
        onEntered: {
            textBox.color = "white"
        }
        onExited: {
            textBox.color = "white"
        }
    }
}
