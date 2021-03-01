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
        visible: qmlAdapter.entryScreenVisible
    }
    GameScreen_Lobby{
        id:gameScreen_Lobby
        visible: qmlAdapter.lobbyScreenVisible
    }
    GameScreen_Overview{
        id:gameScreen_Overview
        visible: qmlAdapter.overviewScreenVisible
    }
    GameScreen_FinalScores{
        id:gameScreen_FinalScores
        visible: qmlAdapter.fscoresScreenVisible
    }
    GameScreen_MainMenu{
        id:gameScreen_MainMenu
        visible: qmlAdapter.mainMenuScreenVisible
    }
}


//Window {
//    width: 640
//    height: 480
//    visible: false
//    title: qsTr("Hello World")
//
//}
