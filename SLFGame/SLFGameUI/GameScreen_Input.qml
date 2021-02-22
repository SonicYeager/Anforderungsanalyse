import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Rectangle{
    id: input_window
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
                    ColumnLayout{
                        anchors.fill: parent
                        spacing : 0
                        Rectangle{
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: parent.height * 1/2
                            color: Qt.rgba(0,0,0,0)
                            RowLayout{
                                spacing: 0
                                anchors.fill: parent
                                InfoBox{
                                    Layout.preferredWidth: parent.width * 1/2 -5
                                    Layout.preferredHeight: parent.height -5
                                    descriptionText: "Buchstabe"
                                    outputText: qmlAdapter.letter
                                    color: Qt.rgba(0,0,0,0)
                                }
                                InfoBox{
                                    Layout.preferredWidth: parent.width * 1/2 -5
                                    Layout.preferredHeight: parent.height -5
                                    descriptionText: "Runde"
                                    outputText: qmlAdapter.currentRound + " / " + qmlAdapter.maxRounds
                                    color: Qt.rgba(0,0,0,0)
                                }
                            }
                        }
                        Rectangle{
                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: parent.height * 1/2
                            color: Qt.rgba(0,0,0,0)
                            RowLayout{
                                spacing: 0
                                anchors.fill: parent
                                InfoBox{
                                    Layout.preferredWidth: parent.width * 1/2 -5
                                    Layout.preferredHeight: parent.height -5
                                    descriptionText: "Zeit"
                                    outputText: (qmlAdapter.timeLeft === "bis Stop") ? "bis Stop" : qmlAdapter.timeLeft
                                    outputTextColor: (parseInt(qmlAdapter.timeLeft) >= 10 || qmlAdapter.timeLeft === "bis Stop") ? "black" : "red"
                                    color: Qt.rgba(0,0,0,0)
                                }
                                InfoBox{
                                    Layout.preferredWidth: parent.width * 1/2 -5
                                    Layout.preferredHeight: parent.height -5
                                    descriptionText: "Punktzahl"
                                    outputText: qmlAdapter.points
                                    color: Qt.rgba(0,0,0,0)
                                }
                            }
                        }
                    }
                }
            }
        }
        Rectangle{
            id: categoryPlaceholder_top
            Layout.fillHeight: true
            Layout.minimumHeight: 25
            Layout.preferredWidth: parent.width
            color: Qt.rgba(0,0,0,0)
        }
        Categories{
            id:categories
            Layout.preferredWidth: parent.width
            Layout.minimumHeight: listModel.count * 50
            Component.onCompleted: {
                for (var i = 0; i < qmlAdapter.categoryCount; i++)
                {
                    listModel.append({"categoryName":qmlAdapter.getCategoryName(i), "categoryEntry":""})
                }
            }
        }
        Rectangle{
            id: categoryPlaceholder_bottom
            Layout.fillHeight: true
            Layout.minimumHeight: 50
            Layout.preferredWidth: parent.width
            color: Qt.rgba(0,0,0,0)
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
                    text : "STOP"
                    textColor: "white"
                    state: "redButton"
                    fontSize: height * 0.05 + width * 0.05
                    border.width: 3
                    border.color: "white"
                    Layout.leftMargin: parent.width * 0.15
                }
                GameButton
                {
                    Layout.preferredWidth: parent.width * 0.25
                    text : "LEAVE GAME"
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
