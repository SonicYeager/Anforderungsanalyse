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

    delegate: AnswerBlock {
        id: answerBlock
        width : 200
        height: 150
        answer: model.answer
        decision : qmlAdapter.getDecision(qmlAdapter.activeOverviewItem)
        onDecisionChanged: {
            qmlAdapter.setDecision(qmlAdapter.activeOverviewItem, decision)
        }
    }
    model: ListModel{
         id:list_model
    }
}
