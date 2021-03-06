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
    property alias textColor : text_name.color
    Text {
        id: text_name
        color:"black"
        font.pointSize: 14
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.margins: 5
    }
    states: [

        State{
            name: "desc"
            PropertyChanges {
                target: textBox
                color: "black"
                border.width: 0.5
            }
            PropertyChanges {
                target: text_name
                color: "white"
            }
        },
        State{
            name: "active"
            PropertyChanges {
                target: textBox
                color: "#9cba8d"
                border.color:"#383838"
            }
            PropertyChanges {
                target: text_name
                color: "black"
            }
       },
        State{
            name: "semiwhite"
            PropertyChanges {
                target: textBox
                color: "#cfcfcf"
                border.color:"#383838"
            }
            PropertyChanges {
                target: text_name
                color: "black"
            }
       }

    ]
}
