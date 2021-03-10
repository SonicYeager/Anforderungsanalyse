import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

ListView {
    id: list
    property alias count: list_model.count
    property alias listModel: list_model
    spacing: 5
    interactive: false

    delegate: TextBox {
        id: player
        text: model.text
        width : 200
        height: 50
        radius: 90
        color: (index === qmlAdapter.playerId) ? "#6fb1c9" : "white"
    }
    model: ListModel{
         id:list_model
    }
}
