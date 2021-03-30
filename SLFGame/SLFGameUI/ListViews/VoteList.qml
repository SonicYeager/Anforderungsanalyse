import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "../Components"
ListView {
    id: list
    property alias count: list_model.count
    property alias listModel: list_model
    property var answerIDX : 0
    spacing: 5
    interactive: false
    orientation: ListView.Horizontal
    delegate: Votebox {
        id: voteBox
        width : 25
        height: 25
        property bool valid: qmlAdapter.getDecision(qmlAdapter.activeOverviewItem, answerIDX, index)
        state: valid? "valid": "invalid"
    }
    model: ListModel{
         id:list_model
    }
}
