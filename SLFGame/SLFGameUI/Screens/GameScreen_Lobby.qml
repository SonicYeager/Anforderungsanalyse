import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import "../Modules"
import "../Components"
import "../ListViews"

Rectangle {
    id: lobby_window
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
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
            color: Qt.rgba(0,0,0,0)
            RowLayout{
                anchors.fill: parent
                spacing: 0
                Rectangle{
                    id: playerOverviewContainer
                    Layout.preferredWidth: 240
                    Layout.preferredHeight: parent.height - 20
                    Layout.leftMargin: 10
                    color: "#000000"
                    border.color: "white"
                    border.width: 3
                    Rectangle{
                        Layout.preferredWidth: parent.width
                        Layout.preferredHeight: parent.height
                        color: Qt.rgba(0,0,0,0)
                        ColumnLayout{
                            anchors.fill: parent
                            spacing:0
                            TextBox {
                                text: "Players"
                                state: "desc"
                                Layout.preferredWidth: 200
                                Layout.preferredHeight: 50
                                Layout.margins: 20
                                Layout.bottomMargin: 10
                            }
                            PlayerOverview {
                                id:playersOverview
                                Layout.preferredWidth: parent.width
                                Layout.minimumHeight: count * 50
                                Layout.leftMargin: 20
                                model: qmlAdapter.players
                            }
                        }
                    }
                }
                Rectangle{
                    id: settingsContainer
                    Layout.preferredWidth: parent.width * 0.45
                    Layout.preferredHeight: parent.height - 20
                    Layout.leftMargin: 20
                    color: "#000000"
                    border.color: "white"
                    border.width: 3
                    Rectangle{
                        id: settingsPlaceholder_top
                        Layout.fillHeight: true - 20
                        Layout.minimumHeight: 25 - 20
                        Layout.preferredWidth: parent.width
                        color: Qt.rgba(0,0,0,0)
                        Layout.margins: 10
                    }
                    Settings_Lobby {
                        id:settings_lobby
                        Layout.preferredWidth: parent.width - 20
                        Layout.preferredHeight: (parent.height - bottom.height - header.height) * 0.8 - 20
                        Layout.margins: 10
                    }
                    Rectangle{
                        id: settingsPlaceholder_bottom
                        Layout.fillHeight: true - 20
                        Layout.minimumHeight: 50 - 20
                        Layout.preferredWidth: parent.width
                        color: Qt.rgba(0,0,0,0)
                        Layout.margins: 10
                    }
                }
                Chat {
                    id: chatbox
                    Layout.fillWidth: true
                    Layout.leftMargin: 20
                    Layout.rightMargin: 10
                    Layout.preferredHeight: parent.height - 20
                    color: Qt.rgba(0,0,0,0)
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
                            qmlAdapter.triggerStateChange(2);
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
                            qmlAdapter.view = "MainMenu";
                        }
                    }
                }
            }
        }
    }
}
