import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "../Components"

Rectangle {
    Layout.preferredWidth: 900
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
        //--SLFComboBox {
        //--    id: cb_decision
        //--    Layout.preferredWidth: 200
        //--    Layout.preferredHeight: 30
        //--    model: [ "Unbearbeitet",
        //--             "Solo",
        //--             "Einfach",
        //--             "Mehrfach",
        //--             "Ungültig" ]
        //--}
        Rectangle {
            Layout.preferredWidth: 300
            Layout.preferredHeight: 30
            color: Qt.rgba(0,0,0,0)
            border.color: "white"
            border.width: 2
            RowLayout {
                anchors.fill: parent
                spacing: 0
                VoteList {
                    id: voteList
                    Layout.preferredWidth: listModel.count * 30
                    Layout.minimumHeight: 30
                    Component.onCompleted: {
                        for (var i = 0; i < qmlAdapter.playerCount; i++)
                        {
                           listModel.append({})
                        }
                    }
                }
            }
        }
    }
}
