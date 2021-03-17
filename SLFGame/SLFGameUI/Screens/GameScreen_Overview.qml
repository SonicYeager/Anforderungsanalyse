import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import "../Modules"
import "../Components"
import "../ListViews"

Rectangle{
    id:lobby_window
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
                Banner{
                    Layout.alignment: Qt.AlignHCenter
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
                    id: categoryOverviewContainer
                    Layout.preferredWidth: parent.width * 0.1
                    Layout.preferredHeight: parent.height - 20
                    Layout.leftMargin: 20
                    Layout.topMargin: 20
                    color: Qt.rgba(0,0,0,0)
                    ColumnLayout{
                        anchors.fill: parent
                        spacing:0
                        CategoryOverview {
                            id:categoryOverview
                            Layout.preferredWidth: 200
                            Layout.minimumHeight: listModel.count * 50
                            Layout.alignment: Qt.AlignTop
                            Component.onCompleted: {
                                for (var i = 0; i < qmlAdapter.categoryCount; i++)
                                {
                                    if (i === 0)
                                        listModel.append({"text":qmlAdapter.getCategoryName(i), "state": "active"})
                                    else
                                        listModel.append({"text":qmlAdapter.getCategoryName(i), "state": "desc"})
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id: answerBlockContainer
                    Layout.preferredWidth: parent.width * 0.5
                    Layout.preferredHeight: parent.height - 20
                    Layout.leftMargin: 20
                    Layout.topMargin: 20
                    color: Qt.rgba(0,0,0,0)
                    ColumnLayout{
                        anchors.fill: parent
                        spacing:0
                        AnswerBlockList {
                            id: answerBlockList
                            Layout.preferredWidth: parent.width
                            Layout.minimumHeight: count * 50
                            Layout.alignment: Qt.AlignTop
                            Component.onCompleted: {
                                for (var i = 0; i < qmlAdapter.playerCount; i++)
                                {
                                    answerBlockList.listModel.append(
                                    {"answer":qmlAdapter.getAnswer(i,qmlAdapter.activeOverviewItem)})
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
                    id: confirmButton
                    Layout.preferredWidth: parent.width * 0.25
                    text : "CONFIRM"
                    textColor: "white"
                    state: "inactive"
                    fontSize: height * 0.05 + width * 0.05
                    border.width: 3
                    border.color: "white"
                    Layout.leftMargin: parent.width * 0.15
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            //if (confirmButton.state === "blueButton")
                            qmlAdapter.prepareNextRound();
                        }
                    }
                    Connections {
                        target: qmlAdapter
                        function onDecisionsChanged()
                        {
                            confirmButton.state = "inactive"
                            var allset = 1
                            for (var i = 0; i < qmlAdapter.playerCount; i++)
                                for (var j = 0; j < qmlAdapter.categoryCount; j++)
                                    if (qmlAdapter.getDecision(i,j) === 0)
                                        allset = 0
                            if (allset === 1)
                                confirmButton.state = "blueButton"
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