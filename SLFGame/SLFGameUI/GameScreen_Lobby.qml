import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Rectangle{
    id: lobby_window
    width: parent.width
    height: parent.height
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
            border.width: 5
            Layout.margins: 10
            RowLayout {
                anchors.fill: parent
                spacing: 0
                Rectangle {
                    Layout.fillWidth: true -5
                    Layout.fillHeight: true -5
                    Layout.alignment: Qt.AlignCenter
                    color: Qt.rgba(0,0,0,0)
                }
                Banner{

                }
                Rectangle {
                    Layout.fillWidth: true -5
                    Layout.fillHeight: true -5
                    Layout.alignment: Qt.AlignCenter
                    color: Qt.rgba(0,0,0,0)
                }
            }
        }
        Rectangle {
            id:body
            Layout.preferredWidth: parent.width - body.Layout.margins * 2
            Layout.fillHeight: true
            color: "#000000"
            border.color: "white"
            border.width: 5
            Layout.margins: 10
            RowLayout{
                anchors.fill: parent
                spacing: 0
                Rectangle{
                    color: Qt.rgba(0,0,0,0)
                    id: settingsContainer
                    Layout.preferredWidth: parent.width * 0.4
                    Layout.preferredHeight: parent.height
                    Layout.margins: 20
                    Rectangle{
                        id: settingsPlaceholder_top
                        Layout.fillHeight: true
                        Layout.minimumHeight: 25
                        Layout.preferredWidth: parent.width
                        color: Qt.rgba(0,0,0,0)
                    }
                    Settings_Lobby {
                        id:settings_lobby
                        Layout.preferredWidth: parent.width
                        Layout.preferredHeight: (parent.height - bottom.height - header.height) * 0.8
                    }
                    Rectangle{
                        id: settingsPlaceholder_bottom
                        Layout.fillHeight: true
                        Layout.minimumHeight: 50
                        Layout.preferredWidth: parent.width
                        color: Qt.rgba(0,0,0,0)
                    }
                }
                Rectangle{
                    color: Qt.rgba(0,0,0,0)
                    id: playerOverviewContainer
                    Layout.preferredWidth: parent.width * 0.4
                    Layout.preferredHeight: parent.height
                    Layout.margins: 20
                    Rectangle{
                        Layout.preferredWidth: parent.width
                        Layout.preferredHeight: parent.height*0.8
                        color: Qt.rgba(0,0,0,0)
                        ColumnLayout{
                            anchors.fill: parent
                            spacing:0
                            TextBox {
                                text: "Players"
                                state: "desc"
                                Layout.preferredWidth: 200
                                Layout.preferredHeight: 50
                                Layout.bottomMargin: 5
                            }
                            PlayerOverview {
                                id:playersOverview
                                Layout.preferredWidth: parent.width
                                Layout.minimumHeight: listModel.count * 50
                                Component.onCompleted: {
                                    for (var i = 0; i < qmlAdapter.playerCount; i++)
                                    {
                                        listModel.append({"text": qmlAdapter.getPlayer(i)})
                                    }
                                }
                                Connections {
                                    target: qmlAdapter
                                    function onPlayersChanged()
                                    {
                                        playersOverview.listModel.clear()
                                        for (var i = 0; i < qmlAdapter.playerCount; i++)
                                            playersOverview.listModel.append({"text": qmlAdapter.getPlayer(i)})
                                    }
                                }
                            }
                        }
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
            border.width: 5
            Layout.margins: 10
            Layout.bottomMargin: 30
            RowLayout{
                spacing: 0
                anchors.fill: parent
                GameButton
                {
                    Layout.preferredWidth: parent.width * 0.25
                    text : "START GAME"
                    textColor: "white"
                    state: "blueButton"
                    fontSize: height * 0.05 + width * 0.05
                    border.width: 3
                    border.color: "white"
                    Layout.leftMargin: parent.width * 0.15
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            qmlAdapter.maxRounds = settings_lobby.roundCount
                            qmlAdapter.timeLeft = settings_lobby.roundTime
                            qmlAdapter.prepareGame();
                        }
                    }
                }
                GameButton
                {
                    Layout.preferredWidth: parent.width * 0.25
                    text : "LEAVE LOBBY"
                    textColor: "white"
                    state: "blueButton"
                    fontSize: height * 0.05 + width * 0.05
                    border.width: 3
                    border.color: "white"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            qmlAdapter.lobbyScreenVisible = false;
                            qmlAdapter.mainMenuScreenVisible = true;
                        }
                    }
                }
            }
        }
    }
}
