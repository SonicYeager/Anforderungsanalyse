import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import "../Modules"
import "../Components"

Rectangle{
    id: mainMenu_window
    width: Screen.width
    height: Screen.height
    color: "#1c2b1e"
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        Rectangle{
            id: header
            Layout.minimumHeight: 250
            Layout.minimumWidth: parent.width - header.Layout.margins * 2
            color: "#000000"
            border.color: "white"
            border.width: 3
            Layout.margins: 10
            RowLayout {
                anchors.fill: parent
                spacing: 0
                Banner{
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
        Rectangle{
            id: body
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width - body.Layout.margins * 2
            Layout.alignment: Qt.AlignHCenter
            color: Qt.rgba(0,0,0,0)
            Layout.margins: 5
            Rectangle{
                anchors.centerIn: parent
                width: 500
                height: 500
                color: "#000000"
                border.color: "white"
                border.width: 3
                Layout.margins: 10
                ColumnLayout {
                    spacing: 0
                    anchors.fill: parent
                    TextBox{
                        id: tb_nameDesc
                        text: "Spielername"
                        state: "desc"
                        Layout.preferredWidth: 200
                        Layout.preferredHeight: 50
                        Layout.alignment: Qt.AlignCenter
                        Layout.bottomMargin: 10
                        Layout.topMargin: 60
                    }
                    EntryBox{
                        id: eb_nameEntry
                        text: qmlAdapter.playerName
                        placeholderText: "Name"
                        Layout.preferredWidth: 200
                        Layout.preferredHeight: 50
                        Layout.alignment: Qt.AlignCenter
                        onTextChanged : {
                            qmlAdapter.playerName = text
                        }
                    }

                    Rectangle{
                        id: ph_top
                        Layout.fillHeight: true
                        Layout.preferredWidth: parent.width
                        color: Qt.rgba(0,0,0,0)
                    }
                    GameButton
                    {
                        Layout.preferredWidth: 200
                        Layout.preferredHeight: 50
                        text : "SPIEL HOSTEN"
                        textColor: "white"
                        state: "blueButton"
                        fontSize: height * 0.05 + width * 0.05
                        border.width: 3
                        border.color: "white"
                        Layout.alignment: Qt.AlignCenter
                        radius: 0
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                qmlAdapter.hostLobby();
                                qmlAdapter.view = "Lobby";
                            }
                        }
                    }
                    Rectangle{
                        id: ph_seperator
                        Layout.minimumHeight: 50
                        Layout.preferredWidth: parent.width
                        color: Qt.rgba(0,0,0,0)
                    }
                    GameButton
                    {
                        Layout.preferredWidth: 200
                        Layout.preferredHeight: 50
                        text : "SPIEL BEITRETEN"
                        textColor: "white"
                        state: "blueButton"
                        fontSize: height * 0.05 + width * 0.05
                        border.width: 3
                        border.color: "white"
                        Layout.alignment: Qt.AlignCenter
                        radius: 0
                        Layout.bottomMargin: 5
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                qmlAdapter.joinLobby();
                                qmlAdapter.view = "Lobby";
                            }
                        }
                    }
                    EntryBox {
                        id: lobbyCode
                        text: qmlAdapter.lobbyCode
                        placeholderText: "Lobby IP"
                        Layout.preferredWidth: 200
                        Layout.preferredHeight: 50
                        Layout.alignment: Qt.AlignCenter
                        Layout.bottomMargin: 15
                        onTextChanged: {
                            qmlAdapter.lobbyCode = text;
                        }
                    }

                    Rectangle{
                        id: ph_bot
                        Layout.fillHeight: true
                        Layout.preferredWidth: parent.width
                        color: Qt.rgba(0,0,0,0)
                    }
                }
            }
        }
        Rectangle{
            id: bottom
            Layout.minimumHeight: 100
            Layout.preferredWidth: parent.width * 0.5 - bottom.Layout.margins * 2
            Layout.alignment: Qt.AlignHCenter
            color: "black"
            border.color: "white"
            border.width: 3
            Layout.margins: 10
            RowLayout{
                spacing: 0
                anchors.fill: parent
                GameButton
                {
                    Layout.preferredHeight: 50
                    Layout.preferredWidth: parent.width * 0.25
                    text : "SPIEL VERLASSEN"
                    textColor: "white"
                    state: "blueButton"
                    fontSize: height * 0.05 + width * 0.05
                    border.width: 3
                    border.color: "white"
                    Layout.alignment: Qt.AlignCenter
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            Qt.quit()
                        }
                    }
                }
            }
        }
    }
}
