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
    Loader {
        id: pageLoader
        anchors.fill: parent
        source: "GameScreen_" + qmlAdapter.view + ".qml"
    }
    //Component.onCompleted: pageLoader.source = "GameScreen_" + qmlAdapter.view + ".qml"
    //Connections {
    //    target: qmlAdapter
    //    function onViewChanged()
    //    {
    //        pageLoader.source = "GameScreen_" + qmlAdapter.view + ".qml";
    //    }
    //}
}
