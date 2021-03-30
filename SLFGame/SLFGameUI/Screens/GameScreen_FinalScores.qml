import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import "../Modules"
import "../Components"
import "../ListViews"

Rectangle{
    id: finalscores_window
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
            id: content
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width - content.Layout.margins * 2
            Layout.alignment: Qt.AlignHCenter
            color: Qt.rgba(0,0,0,0)
            Layout.margins: 10
            ColumnLayout{
                spacing: 0
                anchors.fill: parent
                ScoreList{
                    id: firstPlace
                    Layout.preferredWidth: 200
                    Layout.minimumHeight: 100
                    Component.onCompleted: {
                        listModel.append({"playername":qmlAdapter.players(qmlAdapter.finalScores_placements(0)).second,
                                         "score":qmlAdapter.finalScores_scores(0),
                                         "color":"#b08613"})
                    }
                }
                ScoreList{
                    id: secondPlace_and_thirdPlace
                    Layout.preferredWidth: 200
                    Layout.minimumHeight: 100
                    Component.onCompleted: {
                        for (var i = 1; i < qmlAdapter.finalScores_placements.length && i < 3; i++)
                        listModel.append({"playername":qmlAdapter.players(qmlAdapter.finalScores_placements(0)).second,
                                          "score":qmlAdapter.finalScores_scores(0),
                                          "color": (i === 1) ? "#abadb0" : "#b07230"})
                    }
                }
                ScoreList{
                    id: otherPlaces
                    Layout.preferredWidth: 200
                    Layout.minimumHeight: 100
                    Component.onCompleted: {
                        listModel.append({"playername":qmlAdapter.players(qmlAdapter.finalScores_placements(0)).second})
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
            Layout.bottomMargin: 30
            RowLayout{
                spacing: 0
                anchors.fill: parent
                GameButton
                {
                    Layout.preferredWidth: parent.width * 0.25
                    text : "LOBBY"
                    textColor: "white"
                    state: "blueButton"
                    fontSize: height * 0.05 + width * 0.05
                    border.width: 3
                    border.color: "white"
                    Layout.leftMargin: parent.width * 0.15
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                           qmlAdapter.view = "Lobby";
                        }
                    }
                }
                GameButton
                {
                    Layout.preferredWidth: parent.width * 0.25
                    text : "MAIN MENU"
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
