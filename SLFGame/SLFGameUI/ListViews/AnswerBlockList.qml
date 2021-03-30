import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "../Components"

ListView {
    id: list
    property alias count: list_model.count
    property alias listModel: list_model
    property var headerHeight : 55
    interactive: false
    header: headerComponent
    spacing: 5
    delegate: AnswerBlock {
        id: answerBlock
        playerName: qmlAdapter.getPlayer(index)
        width : 800
        height: 30
        answer: qmlAdapter.getAnswer(index, qmlAdapter.activeOverviewItem)
        answerIDX: index
    }
    model: ListModel{
         id:list_model
    }

    Component {
        id: headerComponent
        Rectangle
        {
            color: Qt.rgba(0,0,0,0)
            width: 800
            height: headerHeight
            ColumnLayout {
                anchors.fill:parent
                spacing: 0
                TextBox {
                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: 25
                    color: "white"
                    textColor: "black"
                    text: qmlAdapter.getCategoryName(qmlAdapter.activeOverviewItem)
                    Layout.alignment: Qt.AlignTop
                }
                Rectangle {
                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: 25
                    color: Qt.rgba(0,0,0,0)
                    Layout.bottomMargin: 5
                    RowLayout{
                        anchors.fill: parent
                        spacing: 0
                        TextBox {
                            Layout.preferredWidth: 200
                            Layout.preferredHeight: 25
                            color: "white"
                            textColor: "black"
                            text: "Spieler"
                        }
                        TextBox {
                            Layout.preferredWidth: 200
                            Layout.preferredHeight: 25
                            color: "white"
                            textColor: "black"
                            text: "Antwort"
                        }
                        TextBox {
                            Layout.preferredWidth: 300
                            Layout.preferredHeight: 25
                            color: "white"
                            textColor: "black"
                            text: "Votes"
                        }
                        TextBox {
                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 25
                            color: "white"
                            textColor: "black"
                            text: ""
                        }
                    }
                }
            }
        }
    }
}
