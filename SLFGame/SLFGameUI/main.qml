import QtQuick 2.15
import QtQuick.Window 2.15

Window{
    id: gameScreen_window
    width: Screen.width
    height: Screen.height
    visible: true
    visibility: Window.Maximized
    title: "GameScreen_Input"
    color: "#1c2b1e"
    Loader { id: pageLoader }
    Component.onCompleted: pageLoader.source = "GameScreen_" + qmlAdapter.view + ".qml"
    Connections {
        target: qmlAdapter
        function onViewChanged()
        {
            pageLoader.source = "GameScreen_" + qmlAdapter.view + ".qml";
        }
    }
}


//Window {
//    width: 640
//    height: 480
//    visible: false
//    title: qsTr("Hello World")
//
//}
