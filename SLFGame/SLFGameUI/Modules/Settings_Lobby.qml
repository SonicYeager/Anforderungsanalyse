import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import "../Components"

Rectangle{
    width: parent.width
    height: parent.height
    color: Qt.rgba(0,0,0,0)
    property var roundTime : cb_roundTime.currentText
    property var roundCount : cb_maxRounds.currentText
    ColumnLayout{
        anchors.fill: parent
        spacing: 0
        Rectangle{
            Layout.preferredWidth: 800
            Layout.preferredHeight: 50
            color: Qt.rgba(0,0,0,0)
            Layout.margins: 20
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
                        target:qmlAdapter
                        function onCustomCategoriesChanged()
                        {
                            eb_customCats.text = qmlAdapter.customCategories
                        }
                    }

                    Connections {
                        target: chb_custom
                        function onStateChanged()
                        {
                            eb_customCats.state = (chb_custom.state === "true") ? "active" : "inactive"
                        }
                    }
                }
                CheckBox {
                    id: chb_custom
                    text: "<font color=\"white\">custom</font>"
                    visible: (qmlAdapter.playerId === 0) ? true: false
                    state: qmlAdapter.customChecked
                    onClicked: qmlAdapter.customChecked = checked
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
            Layout.margins: 20
            Layout.bottomMargin: 5
            Layout.topMargin: 5
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
                SLFComboBox{
                    id: cb_roundTime
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 50
                    visible: (qmlAdapter.playerId === 0) ? true : false
                    model: [ "bis Stop", "60", "80", "100", "120", "150", "180", "210" ]
                    onCurrentTextChanged: {
                        qmlAdapter.roundTime = cb_roundTime.currentText
                    }
                }
                EntryBox {
                    id: eb_roundTime
                    visible: (qmlAdapter.playerId === 0)? false : true
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 50
                    Layout.rightMargin: 20
                    text: qmlAdapter.roundTime
                    state: "inactive"
                }
            }
        }
        Rectangle{
            Layout.preferredWidth: 320
            Layout.preferredHeight: 50
            color: Qt.rgba(0,0,0,0)
            Layout.margins: 20
            Layout.bottomMargin: 10
            Layout.topMargin: 5
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
                SLFComboBox{
                    id: cb_maxRounds
                    visible: (qmlAdapter.playerId === 0) ? true : false
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 50
                    model: [ "5","6","7","8","9","10" ]
                    onCurrentTextChanged: {
                        qmlAdapter.maxRounds = cb_maxRounds.currentText
                    }
                }
                EntryBox {
                    id: eb_maxRounds
                    visible: (qmlAdapter.playerId === 0)? false : true
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 50
                    Layout.rightMargin: 20
                    text: qmlAdapter.maxRounds
                    state: "inactive"
                }
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: Qt.rgba(0,0,0,0)
        }
        Rectangle{
            Layout.preferredWidth: 320
            Layout.preferredHeight: 50
            color: Qt.rgba(0,0,0,0)
            Layout.margins: 20
            RowLayout {
                anchors.fill: parent
                spacing: 0
                TextBox{
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 50
                    state: "desc"
                    text: "Lobby IP"
                    Layout.rightMargin: 20
                }
                TextBox{
                    id: lobbycode
                    Layout.preferredWidth: 200
                    Layout.preferredHeight: 50
                    Layout.rightMargin: 0
                    state: "desc"
                    text: qmlAdapter.lobbyCode
                    function getLobbyCodeText ()
                    {
                        return lobbycode.text.toString()
                    }
                }
                GameButton {
                    textColor: "white"
                    text : "Copy"
                    Layout.preferredWidth: 50
                    Layout.preferredHeight: 50
                    border.color: "white"
                    border.width: 1
                    state: "blackButton"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            textEdit.text = qmlAdapter.lobbyCode
                            textEdit.selectAll()
                            textEdit.copy()
                        }
                    }
                }
                TextEdit
                {
                    id: textEdit
                    visible: false
                }
            }
        }
    }
    Connections {
        target:qmlAdapter
        function onPlayerIdChanged()
        {
            eb_maxRounds.visible = true
            eb_roundTime.visible = true
            cb_maxRounds.visible = false
            cb_roundTime.visible = false
        }
    }
}


