import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "../Components"

Rectangle {
    Layout.preferredWidth: 800
    Layout.preferredHeight: 30
    property alias answer : answerTB.text
    property alias textColor : answerTB.textColor
    property alias playerName : player.text
    property alias answerIDX : voteList.answerIDX
    color: Qt.rgba(0,0,0,0)
    RowLayout {
        anchors.fill:parent
        spacing: 0
        TextBox {
            id: player
            text: "Player 1"
            Layout.preferredWidth: 200
            Layout.preferredHeight: 30
            state: "desc"
        }
        TextBox {
            id: answerTB
            Layout.preferredWidth: 200
            Layout.preferredHeight: 30
            text: "ph"
            color: "black"
            textColor: "white"
        }
        Rectangle {
            Layout.preferredWidth: 300
            Layout.preferredHeight: 30
            color: Qt.rgba(0,0,0,0)
            RowLayout {
                anchors.fill: parent
                spacing: 0
                VoteList {
                    id: voteList
                    Layout.preferredWidth: 30 * list_model.count
                    Layout.minimumHeight: 30
                    Layout.alignment: Qt.AlignHCenter
                    Component.onCompleted: {
                        for (var i = 0; i < qmlAdapter.playerCount; i++)
                        {
                           listModel.append({})
                        }
                    }
                }
            }
        }
        GameButton {
            Layout.preferredHeight: 30
            Layout.preferredWidth: 100
            state: "whiteButton"
            text: "Vote"
        }
    }
}
