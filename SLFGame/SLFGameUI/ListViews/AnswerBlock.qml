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
            state: "semiwhite"
        }
        TextBox {
            id: answerTB
            Layout.preferredWidth: 200
            Layout.preferredHeight: 30
            text: "ph"
            state: "semiwhite"
        }
        Rectangle {
            Layout.preferredWidth: 300
            Layout.preferredHeight: 30
            border.color:"#CCCCCC"
            border.width: 0.5
            color: "#303640"
            radius: 5
            RowLayout {
                anchors.fill: parent
                spacing: 0
                VoteList {
                    id: voteList
                    Layout.preferredWidth: 25 * count
                    Layout.minimumHeight: 25
                    Layout.alignment: Qt.AlignCenter
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
            id: voteBtn
            Layout.preferredHeight: 30
            Layout.preferredWidth: 100
            state: "whiteButton"
            text: "Vote ändern"
            MouseArea {
                id: voteMA
                anchors.fill: parent
                onClicked: {
                    qmlAdapter.changeVoteState(answerIDX)
                }
                onPressed: voteBtn.color = "#8c8b8b"
                onReleased: voteBtn.color = "#d6d6d6"
            }
        }
    }
}
