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

    delegate: Votebox {
        id: voteBox
        width : 30
        height: 30
        state: (qmlAdapter.getDecision(answerIDX, qmlAdapter.activeOverviewItem, index) === false)? "invalid" : "valid"
    }
    model: ListModel{
         id:list_model
    }
}
