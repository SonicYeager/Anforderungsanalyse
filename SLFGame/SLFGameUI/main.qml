import QtQuick 2.15
import QtQuick.Window 2.15
import "./Screens"

Window{
    id: gameScreen_window
    width: Screen.width
    height: Screen.height
    minimumWidth: Screen.width
    minimumHeight: Screen.height
    visible: true
    visibility: Window.Maximized
    title: "Stadt Land Fluss"
    color: "#1c2b1e"
    Loader {
        id: pageLoader
        anchors.fill: parent
        source: "./Screens/GameScreen_" + qmlAdapter.view + ".qml"
    }
}
