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
    GameScreen_Input{
        id:gameScreen_Input
        visible: true
    }
    GameScreen_Lobby{
        id:gameScreen_Lobby
        visible: false
    }
}


//Window {
//    width: 640
//    height: 480
//    visible: false
//    title: qsTr("Hello World")
//
//}
