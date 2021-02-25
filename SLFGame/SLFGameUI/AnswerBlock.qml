import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Rectangle {
    Layout.preferredWidth: 200
    Layout.preferredHeight: 150
    property alias answer : answerTB.text
    property alias decision : cb_decision.currentIndex
    property alias textColor : answerTB.textColor
    color: Qt.rgba(0,0,0,0)
    ColumnLayout {
        anchors.fill:parent
        spacing: 0
        TextBox {
            text: "Player 1"
            Layout.preferredWidth: 200
            Layout.preferredHeight: 50
            state: "desc"
            Layout.bottomMargin: 5
        }
        TextBox {
            id: answerTB
            Layout.preferredWidth: 200
            Layout.preferredHeight: 50
            text: "ph"
            color: "white"
            textColor: "black"
            Layout.bottomMargin: 5
        }
        ComboBox {
            id: cb_decision
            Layout.preferredWidth: 200
            Layout.preferredHeight: 50
            model: [ "Unbearbeitet",
                     "Solo",
                     "Einfach",
                     "Mehrfach",
                     "Ungültig" ]
        }
    }
}
