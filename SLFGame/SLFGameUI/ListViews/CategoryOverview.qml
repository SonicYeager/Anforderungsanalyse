import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "../Components"
// might not work

ListView {
    id: list
    property alias count: list_model.count
    property alias listModel: list_model
    interactive: false
    onCurrentIndexChanged: qmlAdapter.activeOverviewItem = currentIndex

    delegate: TextBox {
        id: cat
        text: model.text
        width : 200
        height: 50
        property bool active: list.currentIndex === index
        state: active?"active": "desc"//model.state
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                list.currentIndex = index
            }
        }
    }
    model: ListModel{
         id:list_model
    }
}
