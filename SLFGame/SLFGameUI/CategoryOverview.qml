import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

ListView {
    id: list
    property alias count: list_model.count
    property alias listModel: list_model
    property var spacingSum : spacing * 2
    spacing: 5
    interactive: false

    delegate: TextBox {
        id: cat
        text: model.text
        width : 200
        height: 50
        state: model.state
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                for (var i = 0; i < list.count; i++)
                    list_model.get(i).state = "desc"
                model.state = "active"
                for (var j = 0; j < list.count; j++)
                    if (list_model.get(j).state === "active")
                        qmlAdapter.activeOverviewItem = j
            }
        }
    }
    model: ListModel{
         id:list_model
    }
}
