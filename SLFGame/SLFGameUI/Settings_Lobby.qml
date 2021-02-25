import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Rectangle{
    width: parent.width
    height: parent.height
    color: Qt.rgba(0,0,0,0)
    property var roundTime : cb_roundTime.currentText
    property var roundCount : cb_roundCount.currentText
    ColumnLayout{
        anchors.fill: parent
        spacing: 0
        Rectangle{
            Layout.preferredWidth: 800
            Layout.preferredHeight: 50
            color: Qt.rgba(0,0,0,0)
            Layout.bottomMargin: 5
            RowLayout {
                anchors.fill: parent
                spacing: 0
                TextBox{
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 50
                    state: "desc"
                    text: "Kategorien"
                    Layout.rightMargin: 20
                }
                EntryBox {
                    id: eb_customCats
                    Layout.preferredWidth: 500
                    Layout.preferredHeight: 50
                    text: qmlAdapter.customCategories
                    Layout.rightMargin: 10
                    state: "inactive"
                    onTextChanged: {
                        qmlAdapter.customCategories = text
                    }
                    Connections {
                        target: chb_custom
                        onStateChanged:  {
                            eb_customCats.state = (chb_custom.state === "true") ? "active" : "inactive"
                            if (chb_custom.state === "false")
                                qmlAdapter.customCategories = "Stadt,Land,Fluss,Name,Tier,Beruf"
                        }
                    }
                }
                CheckBox {
                    id: chb_custom
                    text: "<font color=\"white\">custom</font>"
                    state: qmlAdapter.customChecked
                    onClicked: qmlAdapter.customChecked = checked
                    Component.onCompleted: checked = qmlAdapter.customChecked
                    Connections {
                        target: qmlAdapter
                        onCustomCheckedChanged: chb_custom.checked = qmlAdapter.customChecked
                    }
                }
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    color: Qt.rgba(0,0,0,0)
                }
            }
        }
        Rectangle{
            Layout.preferredWidth: 320
            Layout.preferredHeight: 50
            Layout.bottomMargin: 5
            color: Qt.rgba(0,0,0,0)
            RowLayout {
                anchors.fill: parent
                spacing: 0
                TextBox{
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 50
                    state: "desc"
                    text: "Rundenzeit"
                    Layout.rightMargin: 20
                }
                ComboBox{
                    id: cb_roundTime
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 50
                    model: [ "bis Stop", "60", "80", "100", "120", "150", "180", "210" ]
                }
            }
        }
        Rectangle{
            Layout.preferredWidth: 320
            Layout.preferredHeight: 50
            color: Qt.rgba(0,0,0,0)
            Layout.bottomMargin: 40
            RowLayout {
                anchors.fill: parent
                spacing: 0
                TextBox{
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 50
                    state: "desc"
                    text: "Rundenanzahl"
                    Layout.rightMargin: 20
                }
                ComboBox{
                    id: cb_roundCount
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 50
                    model: [ "5","6","7","8","9","10" ]
                }
            }
        }
        Rectangle{
            Layout.preferredWidth: 320
            Layout.preferredHeight: 50
            color: Qt.rgba(0,0,0,0)
            Layout.bottomMargin: 5
            RowLayout {
                anchors.fill: parent
                spacing: 0
                TextBox{
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 50
                    state: "desc"
                    text: "Lobby ID"
                    Layout.rightMargin: 20
                }
                TextBox{
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 50
                    state: "desc"
                    text: qmlAdapter.lobbyCode
                }
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: Qt.rgba(0,0,0,0)
        }
    }
}
