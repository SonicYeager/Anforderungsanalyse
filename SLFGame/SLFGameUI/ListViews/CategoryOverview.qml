import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "../Components"

ListView {
    id: list
    property alias count: list_model.count
    property alias listModel: list_model
    property var headerHeight: 55
    interactive: false
    onCurrentIndexChanged: qmlAdapter.activeOverviewItem = currentIndex
    header: headerComponent

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

    Component {
        id: headerComponent
        Rectangle
        {
            color: Qt.rgba(0,0,0,0)
            width: 200
            height: headerHeight
            ColumnLayout{
                anchors.fill: parent
                spacing: 0
                TextBox {
                    id: headerTB
                    Layout.minimumWidth: 200
                    Layout.minimumHeight: 50
                    color: "white"
                    textColor: "black"
                    text: "Kategorien"
                    Layout.alignment: Qt.AlignTop
                }
            }
        }
    }
}
