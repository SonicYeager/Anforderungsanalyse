import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Rectangle{
    id:lobby_window
    width: parent.width
    height: parent.height
    color: "#1c2b1e"
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        Rectangle{
            id: header
            Layout.minimumHeight: 200
            Layout.minimumWidth: parent.width - header.Layout.margins * 2
            color: "#000000"
            border.color: "white"
            border.width: 5
            Layout.margins: 10
            RowLayout {
                anchors.fill: parent
                spacing: 0
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
            Layout.preferredHeight: parent.height * 0.4
            color: Qt.rgba(0,0,0,0)
            Layout.margins: 10
            RowLayout{
                anchors.fill: parent
                spacing: 0
                Rectangle{
                    color: Qt.rgba(0,0,0,0)
                    id: categoryOverviewContainer
                    Layout.preferredWidth: parent.width * 0.2
                    Layout.preferredHeight: parent.height
                    Layout.margins: 20
                    Layout.leftMargin: 40
                    Rectangle{
                        Layout.preferredWidth: parent.width
                        Layout.preferredHeight: parent.height*0.8
                        color: Qt.rgba(0,0,0,0)
                        ColumnLayout{
                            anchors.fill: parent
                            spacing:0
                            CategoryOverview {
                                id:categoryOverview
                                Layout.preferredWidth: parent.width
                                Layout.minimumHeight: listModel.count * 50
                                Component.onCompleted: {
                                    for (var i = 0; i < qmlAdapter.categoryCount; i++)
                                    {
                                        if (i === 0)
                                            listModel.append({"text":qmlAdapter.getCategoryName(i), "state": "active"})
                                        else
                                            listModel.append({"text":qmlAdapter.getCategoryName(i), "state": "desc"})
                                    }
                                }
                                Connections {
                                    target: qmlAdapter
                                    function onCategoryCountChanged()
                                    {
                                        categoryOverview.listModel.clear()
                                        for (var i = 0; i < qmlAdapter.categoryCount; i++)
                                        {
                                            if (i === 0)
                                                categoryOverview.listModel.append({"text":qmlAdapter.getCategoryName(i), "state": "active"})
                                            else
                                                categoryOverview.listModel.append({"text":qmlAdapter.getCategoryName(i), "state": "desc"})
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    color: Qt.rgba(0,0,0,0)
                    id: answerBlockContainer
                    Layout.preferredWidth: parent.width * 0.8
                    Layout.preferredHeight: parent.height
                    Layout.margins: 20
                    Layout.leftMargin: 40
                    Rectangle{
                        Layout.preferredWidth: parent.width
                        Layout.preferredHeight: parent.height*0.8
                        color: Qt.rgba(0,0,0,0)
                        ColumnLayout{
                            anchors.fill: parent
                            spacing:0
                            AnswerBlockList {
                                id: answerBlockList
                                Layout.preferredWidth: parent.width * (listModel.count * 0.1)
                                Layout.minimumHeight: 150
                                Component.onCompleted: {
                                    for (var i = 0; i < qmlAdapter.playerCount; i++)
                                    {
                                            listModel.append({"answer":" "})
                                    }
                                }
                                Connections {
                                    target: qmlAdapter
                                    function onAnswersChanged()
                                    {
                                        answerBlockList.listModel.clear()
                                        for (var i = 0; i < qmlAdapter.playerCount; i++)
                                        {
                                            answerBlockList.listModel.append(
                                                        {"answer":qmlAdapter.getAnswer(qmlAdapter.activeOverviewItem),
                                                            "decision":qmlAdapter.getDecision(qmlAdapter.activeOverviewItem)})
                                        }
                                    }
                                    function onActiveOverviewItemChanged()
                                    {
                                        answerBlockList.listModel.clear()
                                        for (var i = 0; i < qmlAdapter.playerCount; i++)
                                        {
                                            answerBlockList.listModel.append(
                                                        {"answer":qmlAdapter.getAnswer(qmlAdapter.activeOverviewItem),
                                                            "decision":qmlAdapter.getDecision(qmlAdapter.activeOverviewItem)})
                                        }
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
                    text : "CONFIRM"
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
                            qmlAdapter.lobbyScreenVisible = false;
                            qmlAdapter.entryScreenVisible = true;
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
                }
            }
        }
    }
}
