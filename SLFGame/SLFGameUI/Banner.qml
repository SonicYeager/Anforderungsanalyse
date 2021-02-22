import QtQuick 2.0

Rectangle {
    width: 320
    height: 200
    color:Qt.rgba(0,0,0,0)
    Image{
        anchors.fill: parent
        source: "resources/banner.png"
        sourceSize.width: 400
        sourceSize.height: 250
    }
}
