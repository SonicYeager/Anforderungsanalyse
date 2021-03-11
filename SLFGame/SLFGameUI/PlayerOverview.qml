import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

ListView {
    id: list
    spacing: 5
    interactive: false

    delegate: TextBox {
        id: player
        text: modelData.name
        width : 200
        height: 50
        radius: 90
        color: (modelData.id === qmlAdapter.playerId) ? "#6fb1c9" : "white"
    }
}
