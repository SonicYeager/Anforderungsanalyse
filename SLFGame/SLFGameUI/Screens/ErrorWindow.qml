import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import "../Components"
Window{
    id: errorWindow
    width: 500
    height: 300
    x: Screen.width / 2 - width/2
    y: Screen.height /2 - height/2
    minimumWidth: 500
    minimumHeight: 300
    visible: true
    title: "Info"
    color: "#1c2b1e"
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        TextBox {
            Layout.preferredHeight: 100
            Layout.preferredWidth: 400
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 20
            state: "desc"
            text: "Verbindung zum Host fehlgeschlagen."
        }
        GameButton{
            Layout.preferredWidth: 100
            Layout.preferredHeight: 50
            Layout.alignment: Qt.AlignHCenter
            state: "whiteButton"
            text: "Okay :("
            MouseArea {
                id: ma
                anchors.fill: parent
                onClicked: {errorWindow.close()}
            }
        }

    }
}
