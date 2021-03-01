import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Rectangle{
    id: mainMenu_window
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
        Rectangle{
            id: body
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width - body.Layout.margins * 2
            Layout.alignment: Qt.AlignHCenter
            color: Qt.rgba(0,0,0,0)
            Layout.margins: 10
            //Layout.bottomMargin: 30
            Rectangle{
                anchors.centerIn: parent
                width: 500
                height: 500
                color: Qt.rgba(0,0,0,0)
                ColumnLayout {
                    spacing: 0
                    anchors.fill: parent
                    Rectangle{
                        id: ph_top
                        Layout.fillHeight: true
                        Layout.minimumHeight: 50
                        Layout.preferredWidth: parent.width
                        color: Qt.rgba(0,0,0,0)
                    }
                    GameButton
                    {
                        Layout.preferredWidth: 200
                        Layout.preferredHeight: 50
                        text : "HOST GAME"
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
                                qmlAdapter.mainMenuScreenVisible = false;
                                qmlAdapter.lobbyScreenVisible = true;
                                //qmlAdapter.startHost();
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
                        text : "JOIN GAME"
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
                                qmlAdapter.mainMenuScreenVisible = false;
                                qmlAdapter.lobbyScreenVisible = true;
                                //qmlAdapter.joinHost(lobbyCode.text);
                            }
                        }
                    }
                    EntryBox {
                        id: lobbyCode
                        text: ""
                        Layout.preferredWidth: 200
                        Layout.preferredHeight: 50
                        Layout.alignment: Qt.AlignCenter
                    }

                    Rectangle{
                        id: ph_bot
                        Layout.fillHeight: true
                        Layout.minimumHeight: 50
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
            border.width: 5
            Layout.margins: 10
            Layout.bottomMargin: 30
            RowLayout{
                spacing: 0
                anchors.fill: parent
                GameButton
                {
                    Layout.preferredWidth: parent.width * 0.25
                    text : "LEAVE GAME"
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
