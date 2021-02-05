import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Window{
    id: gameScreen_window
    width: Screen.width
    height: Screen.height
    visible: true
    visibility: Window.Maximized
    title: "GameScreen_Input"
    color: "#000000"
    RowLayout{
        anchors.fill: parent
        spacing: 0
        Rectangle{
            id: categoryContainer
            color: "#333348"
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 2/3 * parent.width
            Layout.preferredHeight: parent.height
            ColumnLayout
            {
                anchors.fill: parent
                spacing: 0
                Rectangle{
                    id: categoryPlaceholder_top
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.width
                    opacity:0
                }
                Categories{
                    id:categories
                    Layout.preferredWidth: parent.width
                    Layout.minimumHeight: 50 * categories.count
                    Component.onCompleted: {
                        for (var i = 0; i < qmlAdapter.categoryCount; i++)
                        {
                            listModel.append({"categoryName":qmlAdapter.getCategoryName(i), "categoryEntry":" "})
                        }
                    }
                }

                Rectangle{
                    id: categoryPlaceholder_bottom
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.width
                    opacity:0
                }
            }
        }
        Rectangle{
            id: overviewContainer
            color: "#333348"
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 1/3 * parent.width
            Layout.preferredHeight: parent.height
            ColumnLayout{
                anchors.fill: parent
                spacing: 0
                Rectangle{
                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: parent.height * 1/6
                    RowLayout{
                        spacing: 0
                        anchors.fill: parent
                        InfoBox{
                            Layout.preferredWidth: parent.width * 1/2
                            Layout.preferredHeight: parent.height
                            descriptionText: "Buchstabe"
                            outputText: qmlAdapter.letter
                            color: overviewContainer.color
                        }
                        InfoBox{
                            Layout.preferredWidth: parent.width * 1/2
                            Layout.preferredHeight: parent.height
                            descriptionText: "Zeit verbleibend"
                            outputText: qmlAdapter.timeLeft
                            color: overviewContainer.color
                        }
                    }
                }
                Rectangle{
                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: parent.height * 1/6
                    color: "#333348"
                    RowLayout{
                        spacing: 0
                        anchors.fill: parent
                        InfoBox{
                            Layout.preferredWidth: parent.width * 1/2
                            Layout.preferredHeight: parent.height
                            descriptionText: "Runde"
                            outputText: qmlAdapter.currentRound + " / " + qmlAdapter.maxRounds
                            color: overviewContainer.color
                        }
                        InfoBox{
                            Layout.preferredWidth: parent.width * 1/2
                            Layout.preferredHeight: parent.height
                            descriptionText: "Punktzahl"
                            outputText: qmlAdapter.points
                            color: overviewContainer.color
                        }
                    }
                }
                Rectangle{
                    Layout.preferredWidth: parent.width * 1/6
                    Layout.preferredHeight: parent.height * 1/6
                    color: "#333348"
                    RowLayout{
                        spacing: 0
                        anchors.fill: parent
                        Button {
                            id: endRoundButton
                            text: "Runde beenden"
                            onClicked : {
                            }
                        }
                        Button {
                            id: exitGameBtn
                            text: "Spiel verlassen"
                            onClicked : {
                            }
                        }
                    }
                }
                Rectangle{
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    opacity: 0
                }
            }
        }
    }
}
