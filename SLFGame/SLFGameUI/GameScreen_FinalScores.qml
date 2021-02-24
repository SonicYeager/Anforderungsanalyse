import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Rectangle{
    id: finalscores_window
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
        Rectangle{
            id: content
            Layout.minimumHeight: 500
            Layout.preferredWidth: parent.width - content.Layout.margins * 2
            Layout.alignment: Qt.AlignHCenter
            color: "black"
            border.color: "white"
            border.width: 5
            Layout.margins: 10
            //Layout.bottomMargin: 30
            RowLayout{
                spacing: 0
                anchors.fill: parent
                Rectangle
                {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height
                    color: Qt.rgba(0,0,0,0)
                }
                InfoBox{
                    Layout.preferredWidth: parent.width * 0.5
                    Layout.preferredHeight: parent.height
                    descriptionText: "Points"
                    outputText: qmlAdapter.points
                    color: Qt.rgba(0,0,0,0)
                }
                Rectangle
                {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height
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
                    text : "LEAVE"
                    textColor: "white"
                    state: "blueButton"
                    fontSize: height * 0.05 + width * 0.05
                    border.width: 3
                    border.color: "white"
                    Layout.alignment: Qt.AlignCenter
                }
            }
        }
    }
}
