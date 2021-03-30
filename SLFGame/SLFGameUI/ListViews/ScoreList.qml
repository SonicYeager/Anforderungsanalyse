import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "../Components"
ListView {
    id: list
    property alias count: list_model.count
    property alias listModel: list_model
    spacing: 5
    interactive: false
    orientation: ListView.Horizontal
    delegate: Rectangle{
        width: 200
        height: 100
        color: Qt.rgba(0,0,0,0)
        ColumnLayout {
            spacing: 0
            anchors.fill:parent
            TextBox {
                Layout.width: 200
                Layout.height: 50
                color: model.color
                text: model.playername
                textColor: "black"
            }
            TextBox {
                Layout.width: 200
                Layout.height: 50
                text: model.score
                color: "white"
                textColor: "black"
            }
        }
    }
    model: ListModel{
         id:list_model
    }
}
