import QtQuick 2.0
import QtQuick.Controls 2.5

TextField {
    id: entryBox
    color:"black"
    text: "_"
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
}
